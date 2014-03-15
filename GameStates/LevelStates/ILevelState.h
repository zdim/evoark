#pragma once
#include "../GameState.h"
class ILevelState :
	public CGameState
{
public:
	ILevelState();
	virtual ~ILevelState();
};

