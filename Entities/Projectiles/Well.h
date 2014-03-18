#pragma once
#include "GravityProjectile.h"
class CWell :
	public CGravityProjectile
{

public:
	CWell();
	virtual ~CWell();

	void HandleCollision(IEntity* other) override;
};

