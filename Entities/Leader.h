#pragma once

#include <vector>
#include "Ships\Ship.h"
typedef std::vector<IEntity*> EntityGroup; //needed for both entity manager and leader

class Coordinator;
class CLeader
{
	enum class LeaderState { Attack, Search, Return, Stay, Backup };
	CShip* target;
	EntityGroup members;
	std::vector<SGD::Point> destinations;
	int totalHull;
	SGD::Point home;
	SGD::Point position;
	Coordinator* coordiantor;
	LeaderState state;
	float timer;
	float abilityDelay;

	void CalculateDestinations();
public:
	CLeader();
	~CLeader();
	int GetCurrentHull();
	bool Assign(const EntityGroup& flock);
	void Update(float dt);
	void SetState(LeaderState newState, SGD::Point location);
	void SetHome(SGD::Point location) {home = location;}
};

class Coordinator
{
	std::vector<CLeader*> leaders;
	
public:
	CLeader* GetClosestLeader(CLeader* leader); //Returns the a CLeader that is closest to the one passed in without being the same one.
	void HandleEvent(); //Fill in when event system is ready.
};