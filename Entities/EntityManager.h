#pragma once
#include "Entity.h"
#include <vector>
#include "Leader.h"
#include "../SGD Wrappers/SGD_Handle.h"

class CEntityManager
{
	std::vector<CLeader*> leaders;
	CEntity* player = nullptr;
	EntityGroup allies;
	EntityGroup smallEnemies;
	EntityGroup bigEnemies;
	EntityGroup ships;
	EntityGroup projectiles;
	EntityGroup asteroids;
	EntityGroup barriers;
	EntityGroup gravObjects;
	Coordinator* coordinator;
	std::vector<SGD::HTexture> images;

public:

	void Spawn(EntityType type, SGD::Point position, unsigned int amount = 1, bool coord = false); //Spawns either one entity, or a flock of enemies, making the leader object in the process
	void SpawnProjectile();
	void ClearTargeted(CEntity* entity);	//Iterates through the groups that could potentially have this entity targeted, and tells them to untarget it.
	void Destroy(CEntity* entity);	//Calls ClearTargeted() on the given entity, then entity->release, and erases the pointer from the list.
	void DestroyGroup(EntityType group);	//Iterates through every entity in a group, calling Destroy()
	void DestroyAll();	//Calls DestroyGroup on all groups
	void CheckCollision(EntityGroup& group1, EntityGroup& group2);
	bool CEntityManager::ShapedCollisions(IEntity* thing1, IEntity* thing2);
	float circleLineInterection(SGD::Point circlePos, float radius, SGD::Point p1, SGD::Point p2);	// < 0 means no intersection. == 0 means one intersction point. > 0 means 2 intersection points.
	bool circlecollision(IEntity* circle1, IEntity* circle2);
	bool circleRectCollision(IEntity* circle, IEntity* rect);
	bool rectCollision(IEntity* rect1, IEntity* rect2);

	void Update(float dt);
	void Render();
	CEntityManager();
	~CEntityManager();
};

