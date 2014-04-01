#pragma once
#include "IEntity.h"
#include "../SGD Wrappers/SGD_Geometry.h"

#define GRAVDECAY 0.025F
#define COLLISION_MODIFIER 0.005F


class CEntity :
	public IEntity
{
protected:
	SGD::HTexture image = SGD::INVALID_HANDLE;
	SGD::Point position = SGD::Point{0,0};
	SGD::Vector velocity = SGD::Vector{0,0};
	SGD::Vector gravVec = SGD::Vector{ 0, 0 };
	float rotation = 0.0f;
	float rotSpeed = SGD::PI;
	SGD::Size size = SGD::Size{ 16, 16 };
	SGD::Size imageSize = SGD::Size{0, 0};
	unsigned int refCount = 1;

	SGD::Point offsetToCamera();
	void rotateToward(SGD::Vector direction, float dt);

	bool destroying = false;

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
	virtual SGD::Rectangle	GetRect() { return SGD::Rectangle{position - size/2, size}; }

	//Mutators
	virtual void SetImage(SGD::HTexture newImage)override;// {image = newImage;}
	virtual void SetPosition(SGD::Point newPos)	override {position = newPos;}
	virtual void SetVelocity(SGD::Vector newVel)override {velocity = newVel;}
	virtual void SetRotation(float newRot)		override {rotation = newRot;}
	virtual void SetSize(SGD::Size newSize)		override {size = newSize;}
	virtual void SetImageSize(SGD::Size newSize)		{ imageSize = newSize;}
	virtual void AddGravity(SGD::Vector grav) override {}

	virtual void HandleCollision(IEntity* other) override;
	//virtual void HandleEvent(CCustomEvent* e) override {};
	
	//Utility. Nothing outside of entity should NEED to use this, but I'm making it public just in case.
	virtual void Clamp();

	virtual void AddRef() final;
	virtual void Release() final;
	virtual void SelfDestruct() override;
};

