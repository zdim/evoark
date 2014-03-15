#pragma once
#include "../IGameState.h"
class ILevelState :
	public IGameState
{
public:
	ILevelState();
	virtual ~ILevelState();
};

