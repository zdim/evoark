#pragma once
#include "IGameState.h"
class CPauseState :
	public IGameState
{
public:
	CPauseState();
	virtual ~CPauseState();
};

