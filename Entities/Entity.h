#pragma once
#include "IEntity.h"
#include "../SGD Wrappers/SGD_Geometry.h"


//Entity, GravityProjectile, and Ship should all return BaseClass to let us know that the entity SHOULD have a more specific type.
//Order IS significant here. All ships are lumped together so we can say if(type > Player && type < Asteroid) or something similar
enum class EntityType { BaseClass,
	Laser, Missile, Push, Well,
	Player, Human, Copperhead, Cobra, Mamba, Coordinator,
	Coral, Moccasin,
	BaseModule, LaserModule, MissileModule, WellModule, PushModule, WarpModule, ShieldModule, EngineModule,
	Asteroid, Planet, Barrier, Trigger,
	Count };
class CEntity :
	public IEntity
{
protected:
	SGD::HTexture image = SGD::INVALID_HANDLE;
	SGD::Point position = SGD::Point{0,0};
	SGD::Vector velocity = SGD::Vector{0,0};
	SGD::Vector gravVec = SGD::Vector{ 0, 0 };
	float rotation = 0.0f;
	SGD::Size size = SGD::Size{ 16, 16 };
	SGD::Size imageSize = SGD::Size{0, 0};
	unsigned int refCount = 1;

public:
	CEntity();
	virtual ~CEntity();

	virtual void Update(float dt) override;
	virtual void Render() override;

	//Accessors
	virtual int				GetType() override {return (int)EntityType::BaseClass;}
	virtual SGD::HTexture	GetImage() override {return image;}
	virtual SGD::Point		GetPosition() {return position;}
	virtual SGD::Vector		GetVelocity() override { return velocity; }
	virtual float			GetRotation() override { return rotation; }
	virtual SGD::Size		GetSize()	  override { return size; }
	virtual SGD::Vector		GetGravVec() override {return gravVec;}
	virtual bool			IsCircle() override {return false;}

	//Simplify rect collision
	virtual SGD::Rectangle	GetRect() { return SGD::Rectangle{position - size / 2, position + size}; }

	//Mutators
	virtual void SetImage(SGD::HTexture newImage)override {image = newImage;}
	virtual void SetPosition(SGD::Point newPos)	override {position = newPos;}
	virtual void SetVelocity(SGD::Vector newVel)override {velocity = newVel;}
	virtual void SetRotation(float newRot)		override {rotation = newRot;}
	virtual void SetSize(SGD::Size newSize)		override {size = newSize;}
	virtual void SetImageSize(SGD::Size newSize)		{ imageSize = newSize;}
	virtual void AddGravity(SGD::Vector grav) override {}

	virtual void HandleCollision(IEntity* other) override;

	virtual void AddRef() final;
	virtual void Release() final;
};
