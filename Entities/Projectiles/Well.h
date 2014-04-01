#pragma once
#include "GravityProjectile.h"
class CWell :
	public CGravityProjectile
{

public:
	CWell();
	virtual ~CWell();

	int GetType() { return (int)EntityType::Well; }
	void SetRadius(float r) { size = { r * 2, r * 2 }; CGravityProjectile::SetRadius(r); }

	void HandleCollision(IEntity* other) override;
};

