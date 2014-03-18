#pragma once
#include "Entity.h"

class CPlanet : public CEntity
{
public:

	bool IsCircle() override {return true;}
	void Update(float dt) override;

	void HandleCollision(IEntity* other) override;
};