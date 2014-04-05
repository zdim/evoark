#pragma once
#include "Entity.h"
#include <vector>
#include "Leader.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "Ships\Player.h"
#include "Ships\Enemies\Moccasin.h"

struct Flock;
struct ModularFlock;
//class CMoccasin;
class CEntityManager
{
	std::vector<CLeader*> leaders;
	CPlayer* player = nullptr;
	EntityGroup allies;
	EntityGroup smallEnemies;
	EntityGroup bigEnemies;
	EntityGroup ships;
	EntityGroup projectiles;
	EntityGroup asteroids;
	EntityGroup stationaries;
	EntityGroup gravObjects;
	Coordinator* coordinator;
	CEntity* stargate = nullptr;
	CMoccasin* boss = nullptr;
	std::vector<SGD::HTexture> images;

	CEntityManager();
	~CEntityManager();
public:

	static CEntityManager* GetInstance();
	void Initialize();
	void Terminate();

	CPlayer* GetPlayer() { return dynamic_cast<CPlayer*>(player); }
	CEntity* GetStargate() { return dynamic_cast<CEntity*>(stargate); }
	CMoccasin* GetBoss() const {return boss;}
	std::vector<IEntity*> GetAllies() { return allies; }
	IEntity* GetCoordinator();
	//IEntity* GetStargate() { return (IEntity*)stargate; }	void Spawn(EntityType type, SGD::Point position, unsigned int amount = 1, bool coord = false); //Spawns either one entity, or a flock of enemies, making the leader object in the process. Amount is a second entity type for the ally's target.
	void SpawnProjectile(EntityType type, SGD::Point position, SGD::Size ownerSize, float rotation, int damage, unsigned int tier = 1, float radius = -1.0f, IEntity* owner = nullptr); //Spawns a projectile 
	void SpawnCollidable(EntityType type, SGD::Point position, SGD::Size size = { 16, 16 }, SGD::Vector velocity = {0,0}, int eventType = -1);
	void Spawn(EntityType type, SGD::Point position, unsigned int amount = 1, bool coord = false); //Spawns either one entity, or a flock of enemies, making the leader object in the process. Amount is a second entity type for the ally's target.
	//int GetDamageFromEntity(IEntity* entity, EntityType projType);
	void ClearTargeted(IEntity* entity);	//Iterates through the groups that could potentially have this entity targeted, and tells them to untarget it.
	int FindLeaderIndex(IEntity* entity);
	void RemoveFromLeader(IEntity* entity);
	void RemoveFromGroup(EntityGroup& group, IEntity* entity);
	void Destroy(IEntity* entity);	//Calls ClearTargeted() on the given entity, then entity->release, and erases the pointer from the list.
	void DestroyGroup(EntityGroup& group);	//Iterates through every entity in a group, calling Destroy()
	void DestroyAll();	//Calls DestroyGroup on all groups
	void DestroyLeader(CLeader* l);
	void DestroyAllLeaders();
	void CheckCollision(EntityGroup& group1, EntityGroup& group2);
	bool ShapedCollisions(IEntity* thing1, IEntity* thing2);
	float circleLineInterection(SGD::Point circlePos, float radius, SGD::Point p1, SGD::Point p2);	// < 0 means no intersection. == 0 means one intersction point. > 0 means 2 intersection points.
	bool circlecollision(IEntity* circle1, IEntity* circle2);
	bool circleRectCollision(IEntity* circle, IEntity* rect);
	bool rectCollision(IEntity* rect1, IEntity* rect2);

	void Update(float dt);
	void Render();

	void Save();
	void Load();

	//Don't use these outside of load!
	EntityGroup CreateCopperheadLeader(Flock& data);
	EntityGroup CreateCobraLeader(Flock& data);
	EntityGroup CreateMambaLeader(Flock& data);
	EntityGroup CreateCoralLeader(Flock& data);
	void CreateLeader(Flock& data);
	void CreateLeader(ModularFlock& data);
};

