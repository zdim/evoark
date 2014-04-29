#pragma once
#include "Stationary.h"

class CPlanet : public Stationary
{
public:
	CPlanet(){ size = { 256, 256 }; }
	int GetType() override { return (int)EntityType::Planet; }
	bool IsCircle() override {return true;}
	void Update(float dt) override;
	void Render();
	SGD::Size GetSize() { return{ 190, 190 }; }
	void HandleCollision(IEntity* other) override;
};