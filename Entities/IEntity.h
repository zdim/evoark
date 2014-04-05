#pragma once

#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_Declarations.h"
//#include "../Event System/CustomEvent.h"

class CCustomEvent;

//Entity, GravityProjectile, and Ship should all return BaseClass to let us know that the entity SHOULD have a more specific type.
//Order IS significant here. All ships are lumped together so we can say if(type > Player && type < Asteroid) or something similar
enum class EntityType {
	BaseClass,
	Laser, Missile, Push, Well,	//Projectiles
	Player, Human, Copperhead, Cobra, Mamba, Coordinator,	//Small ships
	Coral, Moccasin,	//Big Ships
	BaseModule, ShieldModule, EngineModule, LaserModule,  //Basic Modules
	MissileModule, WellModule, PushModule, WarpModule,	//Ability Modules
	Trigger, InvisTrigger, EventTrigger, Stargate, //LevelEvents
	Barrier, Planet, Shield, ModuleShield, //Stationary Collidables
	Asteroid,	//Mobile Collidables
	Count
};

class IEntity
{
public:
	IEntity();
	virtual ~IEntity();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	
	//Accessors
	virtual int				GetType() = 0;
	virtual SGD::HTexture	GetImage() = 0;
	virtual SGD::Point		GetPosition() = 0;
	virtual SGD::Vector		GetVelocity() = 0;
	virtual float			GetRotation() = 0;
	virtual SGD::Size		GetSize() = 0;
	virtual SGD::Vector		GetGravVec() = 0;
	virtual bool			IsCircle() = 0;

	//Simplify rect collision
	virtual SGD::Rectangle	GetRect() = 0;


	//Mutators
	virtual void SetImage(SGD::HTexture newImage) = 0;
	virtual void SetImageSize(SGD::Size newSize) = 0;
	virtual void SetPosition(SGD::Point newPos) = 0;
	virtual void SetVelocity(SGD::Vector newVel) = 0;
	virtual void SetRotation(float newRot) = 0;
	virtual void SetSize(SGD::Size newSize) = 0;
	virtual void AddGravity(SGD::Vector grav) = 0;

	virtual void HandleCollision(IEntity* other) = 0;
	//virtual void HandleEvent(CCustomEvent* e) = 0;

	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual void SelfDestruct() = 0;
};