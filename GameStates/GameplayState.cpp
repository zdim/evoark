#include "GameplayState.h"
#include "Game.h"
#include "GameState.h"
#include "../TinyXML/tinyxml.h"
#include "../TinyXML/tinystr.h"
#include "../Message System/MessageID.h"

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

void CGameplayState::SaveProfile()
{
	std::string filepath = "Resources/XML/Profiles/";
	if (save.profile == 0 || save.profile >= 4)
		return;
	
	filepath += "profile_" + std::to_string(save.profile) + ".xml";
	TiXmlDocument doc(filepath.c_str());

	//Add form the player element
	TiXmlElement* player = new TiXmlElement("player");
	player->SetAttribute("level", save.playerStat.level);
	player->SetAttribute("exp", save.playerStat.exp);
	player->SetAttribute("expRequired", save.playerStat.expRequired);
	player->SetAttribute("perks",save.playerStat.perks);
	player->SetAttribute("laserLevel", save.playerStat.laserLevel);
	player->SetAttribute("missileLevel", save.playerStat.missileLevel);
	player->SetAttribute("wellLevel", save.playerStat.wellLevel);
	player->SetAttribute("pushLevel", save.playerStat.pushLevel);
	player->SetAttribute("warpLevel", save.playerStat.warpLevel);
	
	//Add the player element to the end of the empty doc.
	doc.LinkEndChild(player);
	//See if the world element is saved
	if (save.world.saved)
	{
		TiXmlElement* world = new TiXmlElement("world");
		world->SetAttribute("saved", "true");
		for (unsigned int i = 0; i < save.world.entities.size(); i++)
		{
			TiXmlElement* entity;
			switch (save.world.entities[i].type)
			{
			case EntityType::Cobra:
				entity = new TiXmlElement("cobra");
				break;
			case EntityType::Copperhead:
				entity = new TiXmlElement("copperhead");
				break;
			case EntityType::Human:
				entity = new TiXmlElement("human");
				break;
			case EntityType::Mamba:
				entity = new TiXmlElement("mamba");
				break;
			case EntityType::Planet:
				entity = new TiXmlElement("planet");
				break;
			case EntityType::Player:
				entity = new TiXmlElement("player");
				break;
			default:
				continue;
			}
			entity->SetAttribute("x", save.world.entities[i].position.x);
			entity->SetAttribute("y", save.world.entities[i].position.y);
			entity->SetAttribute("hull", save.world.entities[i].hull);
			entity->SetAttribute("shield", save.world.entities[i].shield);
		}
		for (unsigned int i = 0; i < save.world.modularEntities.size(); i++)
		{
			TiXmlElement* entity;
			switch (save.world.modularEntities[i].type)
			{
			case EntityType::Coral:
				entity = new TiXmlElement("coral");
				break;
			case EntityType::Moccasin:
				entity = new TiXmlElement("moccasin");
				break;
			default:
				continue;
			}
			for (unsigned int j = 0; j < save.world.modularEntities[i].modules.size(); i++)
			{
				TiXmlElement* mod;
				switch (save.world.modularEntities[i].modules[j].type)
				{
				case EntityType::BaseModule:
					mod = new TiXmlElement("base");
					break;
				case EntityType::EngineModule:
					mod = new TiXmlElement("enigne");
					break;
				case EntityType::LaserModule:
					mod = new TiXmlElement("laser");
					break;
				case EntityType::MissileModule:
					mod = new TiXmlElement("missile");
					break;
				case EntityType::PushModule:
					mod = new TiXmlElement("push");
					break;
				case EntityType::ShieldModule:
					mod = new TiXmlElement("shield");
					break;
				case EntityType::WarpModule:
					mod = new TiXmlElement("warp");
					break;
				case EntityType::WellModule:
					mod = new TiXmlElement("well");
					break;
				default:
					continue;
				}
			}
		}

		for (unsigned int i = 0; save.world.collidables.size(); i++)
		{
			TiXmlElement* col;
			switch (save.world.collidables[i].type)
			{
			case EntityType::Asteroid:
				col = new TiXmlElement("asteroid");
				break;
			case EntityType::Barrier:
				col = new TiXmlElement("barrier");
				break;
			case EntityType::InvisTrigger:
				col = new TiXmlElement("invisTrigger");
				break;
			case EntityType::Planet:
				col = new TiXmlElement("planet");
				break;
			case EntityType::Stargate:
				col = new TiXmlElement("stargate");
				break;
			case EntityType::Trigger:
				col = new TiXmlElement("trigger");
				break;
			default:
				continue;
			}
			//determine triggertype, and save that as an attribute
		}
	}
}

void CGameplayState::LoadProfile()
{

}