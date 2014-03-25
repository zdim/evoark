#pragma once
#include "../IGameState.h"
#include "../../Entities/IEntity.h"
#include "../../Camera.h"
class ILevelState :
	public IGameState
{
public:
	ILevelState();
	virtual ~ILevelState();
	virtual IEntity* GetPlayer() = 0;
	virtual CCamera* GetCam() = 0;
	virtual SGD::Size GetWorldSize() = 0;
};

