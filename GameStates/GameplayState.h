#pragma once
#include "IGameState.h"
#include "ILevelState.h"
//#include "../Entities/Ships/Player.h"
//#include "GameState.h"
#include "../Message System/MessageID.h"
#include <vector>

enum class Level { Tutorial, Gen1, Gen2, Gen3, Waves , Final, LoadedLevel, TestStatic, TestGen };
struct playerData
{
	int level;
	int exp;
	int expRequired;
	int perks;
	int laserLevel;
	int missileLevel;
	int wellLevel;
	int pushLevel;
	int warpLevel;
};

struct waveData
{
	int alliesSaved;
	int enemiesKilled;
};

struct EntityData
{
	EntityType type;
	int hull;
	int shield;
	SGD::Point position;
	bool coord;
};

struct ModularEntityData
{
	EntityType type;
	SGD::Point position;
	std::vector<EntityData> modules;
};

struct Flock
{
	EntityType type;
	SGD::Point home;
	bool backup;
	std::vector<EntityData> members;
};

struct ModularFlock
{
	EntityType type;
	SGD::Point home;
	bool backup;
	std::vector<ModularEntityData> members;
};

struct CollidableData
{
	EntityType type;
	MessageID ID;
	SGD::Point position;
	SGD::Size size;
};

struct worldData
{
	bool saved = false;
	SGD::Size size;
	SGD::Size quadSize;
	std::string background;
	std::vector<EntityData> entities;
	ModularEntityData boss;
	std::vector<Flock> flocks;
	std::vector<ModularFlock> modFlocks;
	std::vector<CollidableData> collidables;
};

struct saveData
{
	unsigned int profile;
	//unsigned int profile;
	playerData playerStat;
	waveData waveStat;
	Level currLevel = Level::Gen1;
	worldData world;
};

class CGameplayState : public IGameState
{
	saveData save;
	CGameplayState(){}
	~CGameplayState(){}
public:
	static CGameplayState* GetInstance();
	virtual bool Input() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Exit() override;
	virtual void Enter() override;

	void SaveProfile();
	saveData LoadProfile();
	void DeleteProfile(unsigned int prof);

	Level GetLevel() {return save.currLevel;}
	void SetLevel(Level l) {save.currLevel = l;}
	void IncrementLevel() { save.currLevel = (Level)(int(save.currLevel) + 1); }
	//friend ILevelState;

	unsigned int GetProfile() {return save.profile;}
	void SetProfile(unsigned int profile) {save.profile = profile;}

	saveData & GetSaveData() {return save;}
	void SetSaveData(saveData s) {save = s;}

	void IncrementAlliesSaved() {save.waveStat.alliesSaved++;}
	void IncrementEnemiesKilled() {save.waveStat.enemiesKilled++;}
};