#pragma once
#include "GravityProjectile.h"
class CPush :
	public CGravityProjectile
{
	SGD::Vector forward;
public:
	CPush();
	virtual ~CPush();
	
	SGD::Vector GetForward() {return forward;}
	void SetForward(SGD::Vector newForward) {forward = newForward;}
	void HandleCollision(IEntity* other) override;

};

