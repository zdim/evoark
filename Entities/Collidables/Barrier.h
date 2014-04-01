#pragma once
#include "Planet.h"

class CBarrier : public CPlanet
{
public:
	int GetType() override { return (int)EntityType::Barrier; }
	bool IsCircle() override {return false;}
	//void HandleCollision(IEntity* other) override;
};