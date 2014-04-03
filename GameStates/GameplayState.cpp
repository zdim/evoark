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

TiXmlElement* nameEntityDataElement(EntityType type)
{
	TiXmlElement* elem;
	switch (type)
	{
	case EntityType::Cobra:
		elem = new TiXmlElement("cobra");
		break;
	case EntityType::Copperhead:
		elem = new TiXmlElement("copperhead");
		break;
	case EntityType::Human:
		elem = new TiXmlElement("human");
		break;
	case EntityType::Mamba:
		elem = new TiXmlElement("mamba");
		break;
	case EntityType::Player:
		elem = new TiXmlElement("player");
		break;
	case EntityType::Coral:
		elem = new TiXmlElement("coral");
		break;
	case EntityType::Moccasin:
		elem = new TiXmlElement("moccasin");
		break;
	case EntityType::BaseModule:
		elem = new TiXmlElement("base");
		break;
	case EntityType::EngineModule:
		elem = new TiXmlElement("enigne");
		break;
	case EntityType::LaserModule:
		elem = new TiXmlElement("laser");
		break;
	case EntityType::MissileModule:
		elem = new TiXmlElement("missile");
		break;
	case EntityType::PushModule:
		elem = new TiXmlElement("push");
		break;
	case EntityType::ShieldModule:
		elem = new TiXmlElement("shield");
		break;
	case EntityType::WarpModule:
		elem = new TiXmlElement("warp");
		break;
	case EntityType::WellModule:
		elem = new TiXmlElement("well");
		break;
	case EntityType::Asteroid:
		elem = new TiXmlElement("asteroid");
		break;
	case EntityType::Barrier:
		elem = new TiXmlElement("barrier");
		break;
	case EntityType::InvisTrigger:
		elem = new TiXmlElement("invisTrigger");
		break;
	case EntityType::Planet:
		elem = new TiXmlElement("planet");
		break;
	case EntityType::Stargate:
		elem = new TiXmlElement("stargate");
		break;
	case EntityType::Trigger:
		elem = new TiXmlElement("trigger");
		break;
	default:
		elem = nullptr;
		break;
	}
	return elem;
}

TiXmlElement* makeEntityDataElement(EntityData& data)
{
	TiXmlElement* entity = nameEntityDataElement(data.type);
	entity->SetAttribute("x", data.position.x);
	entity->SetAttribute("y", data.position.y);
	entity->SetAttribute("hull",data.hull);
	entity->SetAttribute("shield",data.shield);
	entity->SetAttribute("coord",data.coord);
	return entity;
}

TiXmlElement* makeModularDataElement(ModularEntityData& data)
{
	TiXmlElement* entity = nameEntityDataElement(data.type);
	entity->SetAttribute("x", data.position.x);
	entity->SetAttribute("y", data.position.y);
	for (unsigned int i = 0; i < data.modules.size(); i++)
	{
		entity->LinkEndChild(makeEntityDataElement(data.modules[i]));
	}
	return entity;
}

TiXmlElement* makeCollidableElement(CollidableData& data)
{
	TiXmlElement* col = nameEntityDataElement(data.type);
	col->SetAttribute("x", data.position.x);
	col->SetAttribute("y", data.position.y);
	col->SetAttribute("width", data.size.width);
	col->SetAttribute("height", data.size.height);
	col->SetAttribute("ID", (int)data.ID);
}

TiXmlElement* makeFlockElement(Flock& data)
{
	TiXmlElement* flock = new TiXmlElement("flock");
	flock->SetAttribute("x", data.home.x);
	flock->SetAttribute("y",data.home.y);
	flock->SetAttribute("backup", data.backup);
	for (unsigned int i = 0; i < data.members.size(); i++)
	{
		flock->LinkEndChild(makeEntityDataElement(data.members[i]));
	}
}

TiXmlElement* makeModFlockElement(ModularFlock& data)
{
	TiXmlElement* flock = new TiXmlElement("modFlock");
	flock->SetAttribute("x", data.home.x);
	flock->SetAttribute("y", data.home.y);
	flock->SetAttribute("backup", data.backup);
	for (unsigned int i = 0; i < data.members.size(); i++)
	{
		flock->LinkEndChild(makeModularDataElement(data.members[i]));
	}
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
		world->SetAttribute("saved", false);
		for (unsigned int i = 0; i < save.world.entities.size(); i++)
		{
			world->LinkEndChild(makeEntityDataElement(save.world.entities[i]));
		}

		for (unsigned int i = 0; i < save.world.flocks.size(); i++)
		{
			world->LinkEndChild(makeFlockElement(save.world.flocks[i]));
		}

		for (unsigned int i = 0; i < save.world.modFlocks.size(); i++)
		{
			world->LinkEndChild(makeModFlockElement(save.world.modFlocks[i]));
		}

		for (unsigned int i = 0; save.world.collidables.size(); i++)
		{
			world->LinkEndChild(makeCollidableElement(save.world.collidables[i]));
		}
		doc.LinkEndChild(world);
	}
	else
	{
		TiXmlElement* world = new TiXmlElement("world");
		world->SetAttribute("save", false);
		doc.LinkEndChild(world);
	}
}

void CGameplayState::LoadProfile()
{

}