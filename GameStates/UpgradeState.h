#pragma once
#include "../SGD Wrappers/SGD_Handle.h"
#include "IGameState.h"
#include "../Entities/EntityManager.h"
#include "../Menu.h"
class CUpgradeState : public IGameState
{
	enum menuReturn { back, count };
	CMenu* menu;

	enum upgrades {
		laserOne, laserTwo, laserThree, 
		missileOne, missileTwo, missileThree, 
		warpOne, warpTwo, warpThree, 
		wellOne, wellTwo, wellThree, 
		pushOne, pushTwo, pushThree, 
	};

	int cursor = 0;
	CPlayer* player = nullptr;
	std::vector<SGD::Rectangle> buttons;

	SGD::HTexture iconTextures[15];

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

