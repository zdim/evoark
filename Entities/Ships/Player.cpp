//
#include "Player.h"
#include <math.h>
#include <algorithm>
#include <sstream>
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../GameStates/Game.h"
#include "../../Message System/CreateProjectile.h"
#include "../../Camera.h"
#include "../../Event System/CustomEvent.h"
#include "../../Message System/CreateGameOverMessage.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../SoundBox.h"
#include "../Collidables/Shield.h"
#include "../../GameStates/GameplayState.h"
#include "../Collidables/EventTrigger.h"
#include "../../WinMain.h"
#include "../../Graphics/Particles/ParticleSystem.h"

#define SHIELD_SCALE 75
#define HULL_SCALE 125

CPlayer::CPlayer()
{
	maxHull = 750;
	hull = maxHull;
	maxShield = 750;
	shield = maxShield;
	shieldRegen = 500;
	shieldDelay = 2;
	shieldTimer = laserTimer = missileTimer = wellTimer = pushTimer = warpTimer = 20;
	laserDelay = 0.1f;
	missileDelay = 2.0f;
	wellDelay = 8;
	pushDelay = 1;
	warpDelay = 12;
	warpSpeed = 300;
	exp = 0;
	expRequired = 100;
	level = 0;
	perks = 5;

	size = { 60, 89 };

	imageSize = { 64, 128 };

	wellIcon = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/wellIconPurple32.png");
	pushIcon = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/pushIconPurple32.png");
	warpIcon = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/warpIconPurple32.png");

	for (int i = 0; i < 6; i++) tutorialWaitForInput[i] = false;
	for (int i = 0; i < 6; i++) tutorialTriggerHit[i] = false;

	m_Engine = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(5)->GetEmitTime()
		);

	m_Engine->Initialize();
	m_Engine->SetOwner(this);
}


CPlayer::~CPlayer()
{

	SGD::GraphicsManager::GetInstance()->UnloadTexture(wellIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(pushIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(warpIcon);

	m_Engine->Release();
	delete m_Engine;

}

void CPlayer::Update(float dt)
{
	SGD::Vector rotatedOffset = { 0, 45 };
	rotatedOffset.Rotate(rotation);
	enginePos = position + rotatedOffset;

	m_Engine->SetEmitterPosition(enginePos);
	m_Engine->Update(dt);

	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;

	if (levelUpTimer > 0)
		levelUpTimer -= dt;
	if (levelUpTimer < 0)
		levelUpTimer = 0;

	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (CGameplayState::GetInstance()->GetLevel() == Level::Tutorial)
	{
#if ARCADE
		if (tutorialWaitForInput[0])
		{
			//Arcade control check here
			if (input->IsKeyDown(SGD::Key::RButton))
			{
				tutorialWaitForInput[0] = false;
				CreateMissile();
			}
			return;
		}

		if (tutorialWaitForInput[1])
		{
			if (input->IsButtonPressed(0, 2) || input->IsButtonPressed(1, 2))
			{
				tutorialWaitForInput[1] = false;
				Warp();
			}
			return;
		}

		if (tutorialWaitForInput[2])
		{
			if (input->IsButtonPressed(0, 0) || input->IsButtonPressed(1, 0))
			{
				tutorialWaitForInput[2] = false;
				CreateWellController();
			}
			return;
		}

		if (tutorialWaitForInput[3])
		{
			if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
			{
				tutorialWaitForInput[3] = false;
				CreatePush();
			}
			return;
		}

		if (tutorialWaitForInput[4])
		{
			if (input->IsButtonPressed(0, 3) || input->IsButtonPressed(1, 3))
			{
				tutorialWaitForInput[4] = false;
				arrowsOn = !arrowsOn;
			}
			return;
		}

		if (tutorialWaitForInput[5])
		{
			if (input->IsButtonPressed(0, 6) || input->IsButtonPressed(1, 6))
			{
				tutorialWaitForInput[5] = false;
				//CreatePush();
			}
			return;
		}
#else
		if (tutorialWaitForInput[0])
		{
			if (input->IsKeyDown(SGD::Key::RButton) || input->GetTrigger(0) == -1)
			{
				tutorialWaitForInput[0] = false;
				CreateMissile();
			}
			return;
		}

		if (tutorialWaitForInput[1])
		{
			if (input->IsKeyPressed(SGD::Key::Spacebar) || input->IsButtonPressed(0, 8))
			{
				tutorialWaitForInput[1] = false;
				Warp();
			}
			return;
		}

		if (tutorialWaitForInput[2])
		{
			if (input->IsKeyPressed(SGD::Key::Q))
			{
				tutorialWaitForInput[2] = false;
				CreateWell();
				return;
			}
			if (input->IsButtonPressed(0, 4))
			{
				tutorialWaitForInput[2] = false;
				CreateWellController();
				return;
			}
		}

		if (tutorialWaitForInput[3])
		{
			if (input->IsKeyPressed(SGD::Key::E) || input->IsButtonPressed(0, 5))
			{
				tutorialWaitForInput[3] = false;
				CreatePush();
			}
			return;
		}

		if (tutorialWaitForInput[4])
		{
			if (input->IsKeyPressed(SGD::Key::Tab) || input->IsButtonPressed(0, 6))
			{
				tutorialWaitForInput[4] = false;
				arrowsOn = !arrowsOn;
			}
			return;
		}

		if (tutorialWaitForInput[5])
		{
			if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 7))
			{
				tutorialWaitForInput[5] = false;
			}
			return;
		}
#endif
	}
	//Timers
	shieldTimer += dt;
	laserTimer += dt;
	missileTimer += dt;
	wellTimer += dt;
	pushTimer += dt;
	warpTimer += dt;

	if (warpTimer - dt < warpDuration && warpTimer >= warpDuration)
	{
		CCamera::GetInstance()->SetSpeed(speed);
	}

	if (shieldTimer >= shieldDelay)
	{
		shield += int(shieldRegen * dt);
		if (shield > maxShield)
			shield = maxShield;
	}


#if ARCADE
	//Movement
	SGD::Vector dir = SGD::Vector{ 0, 0 };
	SGD::Vector joy = input->GetLeftJoystick(0);
	if(joy == SGD::Vector{0,0})
		joy = input->GetLeftJoystick(1);
	if (joy.y < 0)
		dir.y -= 1;
	if (joy.y > 0)
		dir.y += 1;
	if (joy.x < 0)
		dir.x -= 1;
	if (joy.x > 0)
		dir.x += 1;
	if (dir != SGD::Vector{ 0, 0 })
		dir.Normalize();


	//commented out until finished implementing - was messing up standard input
	if (warpTimer < warpDuration)
	{
		velocity = dir * (speed + warpSpeed);
	}
	else
	{
		velocity = dir * speed;
	}


	//SGD::Point mousePos = { 0, 0 };
	float oldRot = rotation;
	if (input->GetMouseMovement() != SGD::Vector{ 0, 0 })
	{
		SGD::Point mousePos = input->GetMousePosition();
		rotation = atan2(mousePos.y - offsetToCamera().y, mousePos.x - offsetToCamera().x) + SGD::PI / 2;
	}

	//Abilities
	if (input->IsKeyDown(SGD::Key::LButton))
	{
		CreateLaser();
	}
	if (input->IsKeyDown(SGD::Key::RButton))
	{
		CreateMissile();
	}
	if (input->IsButtonPressed(0, 0) || input->IsButtonPressed(1, 0))
	{
		CreateWell();
	}
	if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
	{
		CreatePush();
	}
	if (input->IsButtonPressed(0, 2) || input->IsButtonPressed(1, 2))
	{
		Warp();
	}

	// UI Toggle
	if (input->IsButtonPressed(0, 3) || input->IsButtonPressed(1, 3))
		arrowsOn = !arrowsOn;
#else
	//Movement
	SGD::Vector dir = SGD::Vector{ 0, 0 };
	if (input->IsKeyDown(SGD::Key::W) || input->GetLeftJoystick(0).y < 0)
		dir.y -= 1;
	if (input->IsKeyDown(SGD::Key::S) || input->GetLeftJoystick(0).y > 0)
		dir.y += 1;
	if (input->IsKeyDown(SGD::Key::A) || input->GetLeftJoystick(0).x < 0)
		dir.x -= 1;
	if (input->IsKeyDown(SGD::Key::D) || input->GetLeftJoystick(0).x > 0)
		dir.x += 1;
	if (dir != SGD::Vector{ 0, 0 })
		dir.Normalize();

	//commented out until finished implementing - was messing up standard input
	if (warpTimer < warpDuration)
	{

		velocity = dir * (speed + warpSpeed);
	}
	else
	{
		velocity = dir * speed;
	}


	//SGD::Point mousePos = { 0, 0 };
	float oldRot = rotation;
	if (input->GetMouseMovement() != SGD::Vector{ 0, 0 })
	{
		SGD::Point mousePos = input->GetMousePosition() - SGD::Vector{ size.width, size.height } *.5f;
		rotation = atan2(mousePos.y - offsetToCamera().y, mousePos.x - offsetToCamera().x) + SGD::PI / 2;

	}

	if (input->GetRightJoystick(0) != SGD::Vector{ 0, 0 })
	{
		SGD::Vector rotationVec = { 0, -1 };

		SGD::Vector rightThumb = { 0, 0 };
		if (input->GetRightJoystick(0).y < -.30f)			rightThumb.y -= 1;
		if (input->GetRightJoystick(0).y >  .30f)			rightThumb.y += 1;
		if (input->GetRightJoystick(0).x < -.30f)			rightThumb.x -= 1;
		if (input->GetRightJoystick(0).x >  .30f)			rightThumb.x += 1;
		if (rightThumb != SGD::Vector{ 0, 0 })
		{
			//rightThumb.Normalize();
			rotation = rotationVec.ComputeAngle(input->GetRightJoystick(0));
			if (rotation != SGD::PI)
				rotation *= rotationVec.ComputeSteering(rightThumb);
		}
		else
			rotation = oldRot;
	}

	//rotation = atan2(mousePos.y - offsetToCamera().y, mousePos.x - offsetToCamera().x) + SGD::PI / 2;



	//Abilities
	if (input->IsKeyDown(SGD::Key::LButton) || input->GetTrigger(0) == 1)
	{
		CreateLaser();
	}
	if (input->IsKeyDown(SGD::Key::RButton) || input->GetTrigger(0) == -1)
	{
		CreateMissile();
	}
	if (input->IsKeyPressed(SGD::Key::Q))
	{
		CreateWell();
	}
	if (input->IsButtonPressed(0, 4))
	{
		CreateWellController();
	}
	if (input->IsKeyPressed(SGD::Key::E) || input->IsButtonPressed(0, 5))
	{
		CreatePush();
	}
	if (input->IsKeyPressed(SGD::Key::Spacebar) || input->IsButtonPressed(0, 8))
	{
		Warp();
	}

	// UI Toggle
	if (input->IsKeyPressed(SGD::Key::Tab) || input->IsButtonPressed(0, 6))
		arrowsOn = !arrowsOn;
#endif


	// Position event
	CCustomEvent* e = new CCustomEvent(EventID::position, nullptr, this);
	e->Queue();

	CEntity::Update(dt);
}

void CPlayer::Render()
{
	if (levelUpTimer)
	{
		std::ostringstream levelText;
		levelText << "Level " << level;
		Game::GetInstance()->FontPoiret.Write({ Game::GetInstance()->GetScreenWidth() * .25f, Game::GetInstance()->GetScreenHeight() * .65f + levelUpTimer / 3.f * Game::GetInstance()->GetScreenHeight() * .10f }, levelText.str().c_str(), false, char(levelUpTimer / 3.f * 255));

	}


	m_Engine->Render();

	SGD::Rectangle rShipRegion = SGD::Rectangle(SGD::Point{ 0, 0 }, size);
	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}

	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint, rShipRegion, rotation, size / 2, col);
}

void CPlayer::AddGravity(SGD::Vector grav)
{
	if (warpTimer >= warpDuration)
		gravVec = grav;
}

void CPlayer::CreateLaser()
{
	if (laserTimer <= laserDelay)
		return;
	laserTimer = 0;
	//TODO: Send CreateLaser message
	int damage = 25;
	if (laserLevel >= 1)
		damage += 15;

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, m_shield->GetSize(), rotation, damage, laserLevel, -1.0f, this);
	msg->QueueMessage();
}

void CPlayer::CreateMissile()
{
	if (missileTimer <= missileDelay)
		return;
	missileTimer = 0;
	//TODO: Send CreateMissile message
	int damage = 75;
	//damage *= int(1.5f * missileLevel);
	damage += int(1.5f * missileLevel * damage);
	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Missile, position, m_shield->GetSize(), rotation, damage, missileLevel, -1.0f, this);
	msg->QueueMessage();
}

void CPlayer::CreateWell()
{
	if (wellTimer <= wellDelay)
		return;

	CParticleSystem::GetInstance()->AddEmitterPos(18, SGD::InputManager::GetInstance()->GetMousePosition() - CCamera::GetInstance()->GetOffset());
	CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerWell, false);
	wellTimer = 0;
	//TODO: Send CreateWell message

	if (wellLevel == 0)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, SGD::InputManager::GetInstance()->GetMousePosition() - CCamera::GetInstance()->GetOffset(), size, rotation, 150, wellLevel, 100);
		msg->QueueMessage();
	}
	else if (wellLevel == 1)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, SGD::InputManager::GetInstance()->GetMousePosition() - CCamera::GetInstance()->GetOffset(), size, rotation, 150, wellLevel, 150);
		msg->QueueMessage();
	}
	else
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, SGD::InputManager::GetInstance()->GetMousePosition() - CCamera::GetInstance()->GetOffset(), size, rotation, 225, wellLevel, 150);
		msg->QueueMessage();
	}

}

void CPlayer::CreateWellController()
{
#if !ARCADE
	if (wellTimer <= wellDelay)
		return;

	SGD::Point wellPos;
	SGD::Vector rotationVec = { 0, -1 };
	rotationVec.Rotate(rotation);
	rotationVec *= 300;
	wellPos = this->position + rotationVec;

	CParticleSystem::GetInstance()->AddEmitterPos(18, wellPos);
	CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerWell, false);
	wellTimer = 0;
	//TODO: Send CreateWell message

	if (wellLevel == 0)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, wellPos, size, rotation, 150, wellLevel, 100);
		msg->QueueMessage();
	}
	else if (wellLevel == 1)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, wellPos, size, rotation, 150, wellLevel, 150);
		msg->QueueMessage();
	}
	else
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, wellPos, size, rotation, 225, wellLevel, 150);
		msg->QueueMessage();
	}
#endif
}


void CPlayer::CreatePush()
{
	if (pushTimer <= pushDelay)
		return;
	CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerPush, false);
	pushTimer = 0;


	SGD::Point _pos = offsetToCamera();

	//TODO: Send CreatePush message
	if (pushLevel == 0)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 750, pushLevel, SGD::PI / 4, this);
		msg->QueueMessage();
	}
	else if (pushLevel == 1)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 750, pushLevel, SGD::PI / 2, this);
		msg->QueueMessage();
	}
	else if (pushLevel == 2)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 1000, pushLevel, SGD::PI / 2, this);
		msg->QueueMessage();
	}
	else
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 1000, pushLevel, SGD::PI * 2, this);
		msg->QueueMessage();
	}

}

void CPlayer::Warp()
{


	if (warpTimer <= warpDelay)
		return;

	CParticleSystem::GetInstance()->AddEmitter(15, this);
	CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerWarp, false);
	warpTimer = 0;
	CCamera::GetInstance()->SetSpeed(speed + warpSpeed * 0.5f);
}

void CPlayer::TakeDamage(int damage, bool collision)
{
	if (collision && warpTimer <= warpDuration && warpLevel >= 3)
	{
		return;
	}
	if (collision)
		damage = int((float)damage * COLLISION_MODIFIER);
	shieldTimer = 0;
	if (shield > 0)
	{
		CParticleSystem::GetInstance()->AddEmitter(8, this);
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::enemyShieldDamage, false);
		shield -= damage;
		damage -= shield;
		if (shield <= 0)
			CParticleSystem::GetInstance()->AddEmitter(4, this);
	}
	else
	{
		shield = 0;
	}

	if (damage <= 0)
	{
		return;
	}

	CSoundBox::GetInstance()->Play(CSoundBox::sounds::enemyHullDamage, false);


	hull -= damage;
	float hullPercent = (float)hull / (float)maxHull;
	if (hullPercent < .50f)
		CParticleSystem::GetInstance()->AddEmitter(9, this);


	damaged = .15f;
	if (hull <= 0 && !destroying)
	{
		CParticleSystem::GetInstance()->AddEmitter(20, this);
		CParticleSystem::GetInstance()->AddEmitter(21, this);
		CParticleSystem::GetInstance()->AddEmitter(22, this);
		CParticleSystem::GetInstance()->RemoveEmitter(this);

		CCreateGameOverMessage* msg = new CCreateGameOverMessage();
		msg->QueueMessage();
		SelfDestruct();
	}
}

void CPlayer::AddExp(int _exp)
{
	this->exp += _exp;
	if (this->exp >= expRequired)
	{
		CParticleSystem::GetInstance()->RemoveEmitter(this);

		CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerLevelUp, false);
		level++;
		perks++;
		this->exp = this->exp - expRequired;
		expRequired *= 2;
		maxShield += SHIELD_SCALE;
		maxHull += HULL_SCALE;
		shield = maxShield;
		hull = maxHull;
		levelUpTimer = 3.f;

	}
}

void CPlayer::LaserLevelUp()
{
	laserLevel++;
	if (laserLevel == 3)
		laserDelay = .05f;
}

void CPlayer::WarpLevelUp()
{
	warpLevel++;
	if (warpLevel == 1)
		warpDelay = 6.0f;
	else if (warpLevel == 2)
		warpSpeed = 600.0f;
}

void CPlayer::SetStats(playerData& data)
{
	exp = data.exp;
	expRequired = data.expRequired;
	level = data.level;
	maxShield += SHIELD_SCALE * level;
	maxHull += HULL_SCALE * level;
	hull = maxHull;
	shield = maxShield;
	perks = data.perks;
	//perks = 100;
	for (laserLevel; laserLevel < data.laserLevel; LaserLevelUp());
	for (missileLevel; missileLevel < data.missileLevel; MissileLevelUp());
	for (wellLevel; wellLevel < data.wellLevel; WellLevelUp());
	for (pushLevel; pushLevel < data.pushLevel; PushLevelUp());
	for (warpLevel; warpLevel < data.warpLevel; WarpLevelUp());
}

void CPlayer::HandleCollision(IEntity* other)
{

	if (other == m_shield)
		return;

	if (other->GetType() == (int)EntityType::EventTrigger)
	{
		switch (dynamic_cast<EventTrigger*>(other)->GetTriggerType())
		{
		case (int)triggerID::tutMissiles:
			if (!tutorialTriggerHit[0])
			{
				missileTimer += missileDelay;
				tutorialWaitForInput[0] = true;
				tutorialTriggerHit[0] = true;
			}
			break;
		case (int)triggerID::tutWarp:
			if (!tutorialTriggerHit[1])
			{
				warpTimer += warpDelay;
				tutorialWaitForInput[1] = true;
				tutorialTriggerHit[1] = true;
			}
			break;
		case (int)triggerID::tutWell:
			if (!tutorialTriggerHit[2])
			{
				wellTimer += wellDelay;
				tutorialWaitForInput[2] = true;
				tutorialTriggerHit[2] = true;
			}
			break;
		case (int)triggerID::tutPush:
			if (!tutorialTriggerHit[3])
			{
				pushTimer += pushDelay;
				tutorialWaitForInput[3] = true;
				tutorialTriggerHit[3] = true;
			}
			break;
		case (int)triggerID::tutArrows:
			if (!tutorialTriggerHit[4])
			{
				tutorialWaitForInput[4] = true;
				tutorialTriggerHit[4] = true;
			}
			break;
		case (int)triggerID::tutUpgrade:
			if (!tutorialTriggerHit[5])
			{
				tutorialWaitForInput[5] = true;
				tutorialTriggerHit[5] = true;
			}
			break;
		}
	}

	CShip::HandleCollision(other);


}

int CPlayer::GetTutorialPause()
{
	if (CGameplayState::GetInstance()->GetLevel() != Level::Tutorial)
		return -1;

	for (int i = 0; i < 6; i++)
	{
		if (tutorialWaitForInput[i])
			return i;
	}

	return -1;
}