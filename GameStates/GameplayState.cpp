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
	CTestLevelState* l = CTestLevelState::GetInstance();
	Level lvl = save.currLevel;
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
	//save.currLevel = Level::Gen1;
	//save.playerStat.exp = 0;
	//save.playerStat.laserLevel = 0;
	//save.playerStat.missileLevel = 0;
	//save.playerStat.perks = 15;
	//save.playerStat.pushLevel = 0;
	//save.playerStat.warpLevel = 0;
	//save.playerStat.wellLevel = 0;
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
	if (data.type == EntityType::BaseClass)
	{
		entity = new TiXmlElement("deadMod");
		double x = 0;
		double y = 0;
		entity->SetAttribute("x", x);
		entity->SetAttribute("y", y);
		entity->SetAttribute("hull", 0);
		entity->SetAttribute("shield", 0);
		entity->SetAttribute("coord", false);
		return entity;
	}
	double x = data.position.x;
	double y = data.position.y;
	entity->SetAttribute("x", x);
	entity->SetAttribute("y", y);
	entity->SetAttribute("hull", data.hull);
	entity->SetAttribute("shield", data.shield);
	entity->SetAttribute("coord", data.coord);
	return entity;
}

TiXmlElement* makeModularDataElement(ModularEntityData& data)
{
	TiXmlElement* entity = nameEntityDataElement(data.type);
	entity->SetDoubleAttribute("x", (double)data.position.x);
	entity->SetDoubleAttribute("y", (double)data.position.y);
	for (unsigned int i = 0; i < data.modules.size(); i++)
	{
		entity->LinkEndChild(makeEntityDataElement(data.modules[i]));
	}
	return entity;
}

TiXmlElement* makeCollidableElement(CollidableData& data)
{
	TiXmlElement* col = nameEntityDataElement(data.type);
	col->SetDoubleAttribute("x", (double)data.position.x);
	col->SetDoubleAttribute("y", (double)data.position.y);
	col->SetDoubleAttribute("width", (double)data.size.width);
	col->SetDoubleAttribute("height", (double)data.size.height);
	col->SetAttribute("ID", (int)data.ID);
	return col;
}

TiXmlElement* makeFlockElement(Flock& data)
{
	TiXmlElement* flock = new TiXmlElement("flock");
	flock->SetDoubleAttribute("x", (double)data.home.x);
	flock->SetDoubleAttribute("y", (double)data.home.y);
	flock->SetAttribute("backup", data.backup);
	for (unsigned int i = 0; i < data.members.size(); i++)
	{
		flock->LinkEndChild(makeEntityDataElement(data.members[i]));
	}
	return flock;
}

TiXmlElement* makeModFlockElement(ModularFlock& data)
{
	TiXmlElement* flock = new TiXmlElement("modFlock");
	flock->SetDoubleAttribute("x", (double)data.home.x);
	flock->SetDoubleAttribute("y", (double)data.home.y);
	flock->SetAttribute("backup", data.backup);
	for (unsigned int i = 0; i < data.members.size(); i++)
	{
		flock->LinkEndChild(makeModularDataElement(data.members[i]));
	}
	return flock;
}

void CGameplayState::SaveProfile()
{
	std::string filepath = Game::GetInstance()->GetAppDataPath();
	if (save.profile == 0 || save.profile >= 4)
		return;
	
	filepath += "profile_" + std::to_string(save.profile) + ".xml";
	TiXmlDocument doc(filepath.c_str());
	doc.LoadFile();
	doc.Clear();
	TiXmlElement* deleted = new TiXmlElement("state");
	deleted->SetAttribute("deleted", "false");
	doc.LinkEndChild(deleted);

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

	TiXmlElement* wave = new TiXmlElement("wave");
	wave->SetAttribute("allies", save.waveStat.alliesSaved);
	wave->SetAttribute("enemies", save.waveStat.enemiesKilled);
	doc.LinkEndChild(wave);

	//See if the world element is saved
	if (save.world.saved)
	{
		TiXmlElement* world = new TiXmlElement("world");
		world->SetAttribute("currentLevel", (int)save.currLevel);
		world->SetAttribute("saved", true);
		world->SetDoubleAttribute("quadsWide", (double)save.world.size.width);
		world->SetDoubleAttribute("quadsHigh", (double)save.world.size.height);
		world->SetDoubleAttribute("quadWidth", (double)save.world.quadSize.width);
		world->SetDoubleAttribute("quadHeight", (double)save.world.quadSize.height);
		if (save.world.boss.type == EntityType::BaseClass)
		{
			TiXmlElement* entity = new TiXmlElement("moccasin");
			entity->SetAttribute("x", 0);
			entity->SetAttribute("y", 0);
			TiXmlElement* deadMod = new TiXmlElement("base");
			deadMod->SetDoubleAttribute("x", 0);
			deadMod->SetDoubleAttribute("y", 0);
			deadMod->SetAttribute("hull", 0);
			deadMod->SetAttribute("shield", 0);
			deadMod->SetAttribute("coord", false);
			entity->LinkEndChild(deadMod);
		}
		else
			world->LinkEndChild(makeModularDataElement(save.world.boss));
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

		for (unsigned int i = 0; i < save.world.collidables.size(); i++)
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
	doc.SaveFile();
}

EntityType getElementEntityType(TiXmlElement* elem)
{
	std::vector<EntityType> types;
	std::vector<std::string> strings;

	types.push_back(EntityType::Cobra);
	strings.push_back("cobra");
	types.push_back(EntityType::Copperhead);
	strings.push_back("copperhead");
	types.push_back(EntityType::Human);
	strings.push_back("human");
	types.push_back(EntityType::Mamba);
	strings.push_back("mamba");
	types.push_back(EntityType::Player);
	strings.push_back("player");
	types.push_back(EntityType::Coral);
	strings.push_back("coral");
	types.push_back(EntityType::Moccasin);
	strings.push_back("moccasin");
	types.push_back(EntityType::BaseModule);
	strings.push_back("base");
	types.push_back(EntityType::EngineModule);
	strings.push_back("engine");
	types.push_back(EntityType::LaserModule);
	strings.push_back("laser");
	types.push_back(EntityType::MissileModule);
	strings.push_back("missile");
	types.push_back(EntityType::PushModule);
	strings.push_back("push");
	types.push_back(EntityType::ShieldModule);
	strings.push_back("shield");
	types.push_back(EntityType::WarpModule);
	strings.push_back("warp");
	types.push_back(EntityType::WellModule);
	strings.push_back("well");
	types.push_back(EntityType::Asteroid);
	strings.push_back("asteroid");
	types.push_back(EntityType::Planet);
	strings.push_back("planet");
	types.push_back(EntityType::Stargate);
	strings.push_back("stargate");
	for (unsigned int i = 0; i < strings.size(); i++)
	{
		if (elem->Value() == strings[i])
			return types[i];
	}
	return EntityType::BaseClass;
}

unsigned int flockType(TiXmlElement* elem)
{
	std::string flock = "flock";
	std::string modFlock = "modFlock";
	std::string value = elem->Value();
	if (flock == elem->Value())
		return 1;
	if (modFlock == elem->Value())
		return 2;
	EntityType type = getElementEntityType(elem);
	if (type == EntityType::BaseClass)
		return 0;
	if (type == EntityType::Moccasin)
		return 5;
	if (type <= EntityType::WarpModule)
		return 3;
	if (type >= EntityType::Trigger)
		return 4;

	return 0;
}

EntityData processXmlEntity(TiXmlElement* entity)
{
	EntityData data;
	data.type = getElementEntityType(entity);
	entity->Attribute("hull", &data.hull);
	entity->Attribute("shield", &data.shield);
	double x;
	double y;
	entity->Attribute("x", &x);
	entity->Attribute("y", &y);
	data.position = {(float)x,(float)y};
	int i;
	entity->Attribute("coord", &i);
	data.coord = i != 0;
	return data;
}

ModularEntityData processModularEntity(TiXmlElement* entity)
{
	ModularEntityData data;
	data.type = getElementEntityType(entity);
	double x;
	double y;
	entity->Attribute("x", &x);
	entity->Attribute("y", &y);
	data.position = {(float)x,(float)y};
	TiXmlElement* elem = entity->FirstChildElement();
	while (elem)
	{
		data.modules.push_back(processXmlEntity(elem));
		elem = elem->NextSiblingElement();
	}
	return data;
}

Flock processFlock(TiXmlElement* flock)
{
	Flock data;
	data.type = getElementEntityType(flock->FirstChildElement());
	int i;
	flock->Attribute("backup", &i);
	data.backup = i != 0;
	double x;
	double y;
	flock->Attribute("x", &x);
	flock->Attribute("y", &y);
	data.home = {(float)x,(float)y};
	TiXmlElement* elem = flock->FirstChildElement();
	while (elem)
	{
		data.members.push_back(processXmlEntity(elem));
		elem = elem->NextSiblingElement();
	}
	return data;
}

ModularFlock processModularFlock(TiXmlElement* modFlock)
{
	ModularFlock data;
	data.type = getElementEntityType(modFlock->FirstChildElement());
	int i;
	modFlock->Attribute("backup", &i);
	data.backup = i != 0;
	double x;
	double y;
	modFlock->Attribute("x", &x);
	modFlock->Attribute("y", &y);
	data.home = {(float)x,(float)y};
	TiXmlElement* elem = modFlock->FirstChildElement();
	while (elem)
	{
		data.members.push_back(processModularEntity(elem));
		elem = elem->NextSiblingElement();
	}
	return data;
}

CollidableData processCollidable(TiXmlElement* col)
{
	CollidableData data;
	data.type = getElementEntityType(col);
	double x;
	double y;
	double width;
	double height;
	col->Attribute("x", &x);
	col->Attribute("y", &y);
	col->Attribute("width", &width);
	col->Attribute("height", &height);
	data.position = {(float)x,(float)y};
	data.size = {(float)width, (float)height};
	return data;
}

saveData CGameplayState::LoadProfile()
{
	saveData blank;
	blank.profile = 0;
	std::string filepath = Game::GetInstance()->GetAppDataPath();
	if (save.profile == 0 || save.profile >= 4)
		return blank;

	filepath += "profile_" + std::to_string(save.profile) + ".xml";
	TiXmlDocument doc(filepath.c_str());
	if(!doc.LoadFile())
		return blank;

	TiXmlElement* deleted = doc.FirstChildElement();
	std::string booltrue = "true";
	if (booltrue == deleted->Attribute("deleted"))
		return blank;

	TiXmlElement* player = deleted->NextSiblingElement();
	player->Attribute("level", &save.playerStat.level);
	player->Attribute("exp", &save.playerStat.exp);
	player->Attribute("expRequired", &save.playerStat.expRequired);
	player->Attribute("perks", &save.playerStat.perks);
	player->Attribute("laserLevel", &save.playerStat.laserLevel);
	player->Attribute("missileLevel", &save.playerStat.missileLevel);
	player->Attribute("wellLevel", &save.playerStat.wellLevel);
	player->Attribute("pushLevel", &save.playerStat.pushLevel);
	player->Attribute("warpLevel", &save.playerStat.warpLevel);

	TiXmlElement* wave = player->NextSiblingElement();
	wave->Attribute("allies", &save.waveStat.alliesSaved);
	wave->Attribute("enemies", &save.waveStat.enemiesKilled);

	TiXmlElement* world = wave->NextSiblingElement();
	//std::string buffer = world->Attribute("saved");
	int i;
	world->Attribute("saved", &i);
	save.world.saved = i != 0;
	world->Attribute("currentLevel", &i);
	save.currLevel = (Level)i;
	if (save.world.saved)
	{
		double quadsX;
		double quadsY;
		double quadW;
		double quadH;
		world->Attribute("quadsWide", &quadsX);
		world->Attribute("quadsHigh", &quadsY);
		world->Attribute("quadWidth", &quadW);
		world->Attribute("quadHeight", &quadH);
		save.world.size = { (float)quadsX, (float)quadsY };
		save.world.quadSize = { (float)quadW, (float)quadH };
		save.world.collidables.clear();
		save.world.entities.clear();
		save.world.flocks.clear();
		save.world.modFlocks.clear();
		TiXmlElement* elem = world->FirstChildElement();
		while (elem)
		{
			switch (flockType(elem))
			{
			case 1:
				save.world.flocks.push_back(processFlock(elem));
				break;
			case 2:
				save.world.modFlocks.push_back(processModularFlock(elem));
				break;
			case 3:
				save.world.entities.push_back(processXmlEntity(elem));
				break;
			case 4:
				save.world.collidables.push_back(processCollidable(elem));
				break;
			case 5:
				save.world.boss = processModularEntity(elem);
				if (save.world.boss.modules[0].hull == 0)
				{
					save.world.boss.type = EntityType::BaseClass;
				}
			}
			if (!elem->NextSibling())
			{
				break;
			}
			elem = elem->NextSiblingElement();
		}
	}
	return save;
}

void CGameplayState::DeleteProfile(unsigned int prof)
{
	std::string filepath = Game::GetInstance()->GetAppDataPath();
	if (save.profile == 0 || save.profile >= 4)
		return;

	filepath += "profile_" + std::to_string(prof) + ".xml";
	TiXmlDocument doc(filepath.c_str());
	doc.LoadFile();
	doc.Clear();

	TiXmlElement* deleted = new TiXmlElement("state");
	deleted->SetAttribute("deleted", "true");

	doc.SaveFile();

	unsigned int old = save.profile;
	save.profile = prof;
	LoadProfile();
	save.profile = old;
}