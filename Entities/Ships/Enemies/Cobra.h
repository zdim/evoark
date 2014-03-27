#pragma once
#include "Copperhead.h"
#include "../../Leader.h"
class CCobra :
	public CCopperhead
{
	float warpTimer;
	float warpDelay;
	float warpDuration;
	float warpSpeed;

public:
	CCobra();
	virtual ~CCobra();

	int GetType() override { return (int)EntityType::Cobra; }
	void Update(float dt);
	void AddGrav(SGD::Vector);
	void Warp();
};

class CCobraCoord : public CCobra, public Coordinator
{

};