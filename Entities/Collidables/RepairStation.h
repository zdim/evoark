#pragma once
#include "Stationary.h"

class CRepairStation : public Stationary
{


public:
	CRepairStation(){ size = { 64, 64 }; }
	int GetType() override { return (int)EntityType::Planet; }
	bool IsCircle() override { return true; }
	void Update(float dt) override;

	void HandleCollision(IEntity* other) override;
};
