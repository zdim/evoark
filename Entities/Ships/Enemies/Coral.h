#pragma once
#include "Enemy.h"
#include "../../Leader.h"
class CCoral :
	public CEnemy
{
public:
	CCoral();
	virtual ~CCoral();
};

class CCoralCoord : public CCoral, public Coordinator
{

};