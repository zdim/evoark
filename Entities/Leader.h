#pragma once

#include <vector>
#include "Ships\Enemies\Enemy.h"
typedef std::vector<IEntity*> EntityGroup; //needed for both entity manager and leader

struct EntityData;
struct ModularEntityData;

class Coordinator;
class CLeader
{
	enum class LeaderState { Attack, Search, Return, Stay, Backup };
	CShip* target = nullptr;
	std::vector<CEnemy*> members;
	std::vector<SGD::Point> destinations;
	int totalHull;
	SGD::Point home;
	SGD::Point position;
	Coordinator* coordiantor;
	LeaderState state;
	float timer = 0;
	float abilityDelay = 15.0f;
	float teleportDelay = 15.0f;

	void CalculateDestinations();
	void SetDestinations();
	void Teleport();
	bool DestinationsOffscreen();
public:
	CLeader();
	~CLeader();

	EntityType GetType() { return (EntityType)members[0]->GetType(); }
	int GetCurrentHull();
	bool Assign(const EntityGroup& flock);
	void Update(float dt);
	LeaderState GetState() {return state;}
	void SetState(LeaderState newState, SGD::Point location);
	SGD::Point GetHome() {return home;}
	SGD::Point GetPosition() {return position;}
	void SetHome(SGD::Point location) {home = location;}
	int FindInFlock(IEntity* entity);
	void Remove(IEntity* entity);

	bool IsBackup() {return state == LeaderState::Backup;}

	CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);

	void GetEntityData(std::vector<EntityData>& flockData);
	void GetEntityData(std::vector<ModularEntityData>& flockData);
};

class Coordinator
{
	std::vector<CLeader*> leaders;
	
public:
	virtual ~Coordinator(){}
	CLeader* GetClosestLeader(CLeader* leader); //Returns the a CLeader that is closest to the one passed in without being the same one.
	void HandleEvent(); //Fill in when event system is ready.
};