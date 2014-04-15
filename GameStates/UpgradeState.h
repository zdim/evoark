#pragma once
#include "../SGD Wrappers/SGD_Handle.h"
#include "IGameState.h"
#include "../Entities/EntityManager.h"
class CUpgradeState : public IGameState
{
	enum upgrades {
		laserOne, laserTwo, laserThree, 
		missileOne, missileTwo, missileThree, 
		warpOne, warpTwo, warpThree, 
		wellOne, wellTwo, wellThree, 
		pushOne, pushTwo, pushThree, 
		back
	};

	int cursor = 0;
	CPlayer* player = nullptr;
	std::vector<SGD::Rectangle> buttons;

	SGD::HTexture iconTexture = SGD::INVALID_HANDLE;
	SGD::HTexture upArrowTexture = SGD::INVALID_HANDLE;
public:
	CUpgradeState();
	virtual ~CUpgradeState();

	static CUpgradeState* GetInstance();

	bool Input();
	void Update(float dt);
	void Render();

	void Enter();
	void Exit();
};

