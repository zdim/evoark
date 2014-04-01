#include "GameplayState.h"
#include "Game.h"
#include "GameState.h"
CGameplayState* CGameplayState::GetInstance()
{
	static CGameplayState instance;
	return &instance;
}

bool			CGameplayState::Input()
{
	return true;
}

void			CGameplayState::Update(float dt)
{
	//Should only hit this if the level state has ended.
	//Did the player lose? If so, load the most recent savedata and leveldata fro mthis profile.
	
	//else: The player beat the level.
		//Is it the last level?
			//Play the credits
		//else
			//Load the next level
	//else: The player quit
		//End the state.
		//Ideally, we wont' even hit this in that case, we'll just go straight to exit.

	//Skipping player loss for now.

	//Player beat the level
		//Skipp credits for now.
	CTestLevelState* l = CTestLevelState::GetInstance();
	Level lvl = save.currLevel;
	//l->Enter();
	Game::GetInstance()->PushState(l);
}

void			CGameplayState::Render()
{

}

void			CGameplayState::Exit()
{

}

void			CGameplayState::Enter()
{
	//grab the selected profile from Game, then load save data
	
	//For now: default the save data, and start the test level
	save.currLevel = Level::Gen1;
	save.playerStat.exp = 0;
	save.playerStat.laserLevel = 0;
	save.playerStat.missileLevel = 0;
	save.playerStat.perks = 15;
	save.playerStat.pushLevel = 0;
	save.playerStat.warpLevel = 0;
	save.playerStat.wellLevel = 0;

	//Later: instead of generating a new level, use the save data to locate a .XML with saved level data.
	//Only generate a new level if it is the player was not in the middle of a level
	//CTestLevelState* l = CTestLevelState::GetInstance();
	//l->Enter();
	//^ PushState does that for us! Derp.
	//Game::GetInstance()->PushState(l);
	//... Just do nothing...
}