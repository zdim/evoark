#pragma once

#include <vector>
#include "Ships\Enemies\Enemy.h"
#include "../Event System/IListener.h"
typedef std::vector<IEntity*> EntityGroup; //needed for both entity manager and leader

struct EntityData;
struct ModularEntityData;

class Coordinator;
class CLeader
{
	enum class LeaderState { Search, Return, Stay, Backup };
	CShip* target = nullptr;
	std::vector<CEnemy*> members;
	std::vector<SGD::Point> destinations;
	int totalHull;
	SGD::Point home;
	SGD::Point position;
	SGD::Point backupCall;
	Coordinator* coordiantor;
	LeaderState state;
	float timer = 0;
	float abilityDelay = 15.0f;
	float teleportDelay = 15.0f;
	bool calledBackup = false;

	void CalculateDestinations();
	void SetDestinations();
	void Teleport();
	bool DestinationsOffscreen();
	int CalculateTotalHull();
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
	void SetBackup(SGD::Point location);

	CShip* GetTarget() {return target;}
	void SetTarget(CShip* newTarget);

	void GetEntityData(std::vector<EntityData>& flockData);
	void GetEntityData(std::vector<ModularEntityData>& flockData);
};

class Coordinator : public Listener
{
	std::vector<CLeader*> leaders;
	
public:
	Coordinator();
	virtual ~Coordinator(){}
	void Unregister();
	CLeader* GetClosestLeader(CLeader* leader); //Returns the a CLeader that is closest to the one passed in without being the same one.
	void HandleEvent(CCustomEvent* e) override; //Fill in when event system is ready.
	void AddLeader(CLeader* l);
	void RemoveLeader(CLeader* l);
};