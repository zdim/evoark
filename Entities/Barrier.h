#pragma once
#include "Planet.h"

class CBarrier : public CPlanet
{
public:
	bool IsCircle() override {return false;}
};