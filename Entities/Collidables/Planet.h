#pragma once
#include "Stationary.h"

class CPlanet : public Stationary
{
public:
	CPlanet(){size = { 1024, 1024 };}
	int GetType() override { return (int)EntityType::Planet; }
	bool IsCircle() override {return true;}
	void Update(float dt) override;

	void HandleCollision(IEntity* other) override;
};