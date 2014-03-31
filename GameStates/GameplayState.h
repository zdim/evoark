#pragma once
#include "IGameState.h"
#include "LevelStates\ILevelState.h"
//#include "../Entities/Ships/Player.h"
//#include "GameState.h"

enum class Level { Tutorial, Gen1, Gen2, Gen3, Waves, Final, LoadedLevel, TestStatic, TestGen };
struct playerData
{
	unsigned int exp;
	unsigned int expRequired;
	unsigned int perks;
	unsigned int laserLevel;
	unsigned int missileLevel;
	unsigned int wellLevel;
	unsigned int pushLevel;
	unsigned int warpLevel;
};

struct waveData
{
	unsigned int alliesSaved;
	unsigned int enemiesKilled;
};

struct saveData
{
	playerData playerStat;
	waveData waveStat;
	Level currLevel = Level::Gen1;
};

class CGameplayState : public IGameState
{
	saveData save;
public:
	static CGameplayState* GetInstance();
	virtual bool Input() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Enter() override;

	Level GetLevel() {return save.currLevel;}
	void SetLevel(Level l) {save.currLevel = l;}
	//friend ILevelState;
};