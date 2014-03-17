#pragma once

#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_Declarations.h"

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

	//Mutators
	virtual void SetImage(SGD::HTexture newImage) = 0;
	virtual void SetPosition(SGD::Point newPos) = 0;
	virtual void SetVelocity(SGD::Vector newVel) = 0;
	virtual void SetRotation(float newRot) = 0;
	virtual void SetSize(SGD::Size newSize) = 0;
	virtual void AddGravity(SGD::Vector grav) = 0;

	virtual void HandleCollision() = 0;
	
	virtual void AddRef() = 0;
	virtual void Release() = 0;
};