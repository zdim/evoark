//
#include "Cobra.h"


CCobra::CCobra()
{
}


CCobra::~CCobra()
{
}

void CCobra::Update(float dt)
{
	SGD::Vector dir = CCopperhead::AI(dt);
	
}