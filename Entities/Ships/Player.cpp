//
#include "Player.h"
#include <math.h>
#include <algorithm>
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../Message System/CreateProjectile.h"
#include "../../Camera.h"
#include "../../Event System/CustomEvent.h"
#include "../../Message System/CreateGameOverMessage.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../SoundBox.h"
#include "../Collidables/Shield.h"
#include "../../GameStates/GameplayState.h"
#include "../Collidables/EventTrigger.h"

#include "../../Graphics/Particles/ParticleSystem.h"

#define SHIELD_SCALE 100
#define HULL_SCALE 200

CPlayer::CPlayer()
{
	maxShield = 500;
	shield = maxShield;
	shieldRegen = 500;
	shieldDelay = 2;
	shieldTimer = laserTimer = missileTimer = wellTimer = pushTimer = warpTimer = 20;
	laserDelay = 0.2f;
	missileDelay = 2.0f;
	wellDelay = 12;
	pushDelay = 8;
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
	
	for (int i = 0; i < 4; i++) tutorialWaitForInput[i] = false;
	for (int i = 0; i < 4; i++) tutorialTriggerHit[i] = false;

	m_Engine = CParticleSystem::GetInstance()->GetParticleEffect(5);

	m_Engine->Initialize();
	m_Engine->SetOwner(this);
}


CPlayer::~CPlayer()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(wellIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(pushIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(warpIcon);
}

void CPlayer::Update(float dt)
{
	//SGD::Point test = {position.x

	SGD::Vector rotatedOffset = { 0,45 };
	rotatedOffset.Rotate(rotation);
	enginePos = position + rotatedOffset;


	m_Engine->SetEmitterPosition(enginePos);
	m_Engine->Update(dt);

	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;

	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (CGameplayState::GetInstance()->GetLevel() == Level::Tutorial)
	{
		if (tutorialWaitForInput[0])
		{
			if (input->IsKeyDown(SGD::Key::MouseRight))
			{
				tutorialWaitForInput[0] = false;
				CreateMissile();
			}
			return;
		}

		if (tutorialWaitForInput[1])
		{
			if (input->IsKeyPressed(SGD::Key::Space))
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
			}
			return;
		}

		if (tutorialWaitForInput[3])
		{
			if (input->IsKeyPressed(SGD::Key::E))
			{
				tutorialWaitForInput[3] = false;
				CreatePush();
			}
			return;
		}
	}
	//Timers
	shieldTimer += dt;
	laserTimer += dt;
	missileTimer += dt;
	wellTimer += dt;
	pushTimer += dt;
	warpTimer += dt;

	if (shieldTimer >= shieldDelay)
	{
		shield += int(shieldRegen * dt);
		if (shield > maxShield)
			shield = maxShield;
	}

	//Movement
	SGD::Vector dir = SGD::Vector{0,0};
	if (input->IsKeyDown(SGD::Key::W) || input->GetLeftJoystick(0).y < 0)
		dir.y -= 1;
	if (input->IsKeyDown(SGD::Key::S) || input->GetLeftJoystick(0).y > 0)
		dir.y += 1;
	if (input->IsKeyDown(SGD::Key::A) || input->GetLeftJoystick(0).x < 0)
		dir.x -= 1;
	if (input->IsKeyDown(SGD::Key::D) || input->GetLeftJoystick(0).x > 0)
		dir.x += 1;
	if (dir != SGD::Vector{0, 0})
		dir.Normalize();


	 //commented out until finished implementing - was messing up standard input
	if (warpTimer < warpDuration)
		velocity = dir * (speed + warpSpeed);
	else
	{
		velocity = dir * speed;
	}
	

	//SGD::Point mousePos = { 0, 0 };

	if (input->GetMouseMovement() != SGD::Vector{ 0, 0 })
	{
		SGD::Point mousePos = input->GetMousePosition();
		rotation = atan2(mousePos.y - offsetToCamera().y, mousePos.x - offsetToCamera().x) + SGD::PI / 2;

	}

	if (input->GetRightJoystick(0) != SGD::Vector{ 0, 0 })
	{
		SGD::Vector rotationVec = { 0, -1 };

		SGD::Vector rightThumb = input->GetRightJoystick(0);
		rotation = rotationVec.ComputeAngle(input->GetRightJoystick(0));
		rotation *= rotationVec.ComputeSteering(rightThumb);
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
	if (input->IsKeyPressed(SGD::Key::Q) || input->IsButtonPressed(0, 4))
	{
		CreateWell();
	}
	if (input->IsKeyPressed(SGD::Key::E) || input->IsButtonPressed(0, 5))
	{
		CreatePush();
	}
	if (input->IsKeyPressed(SGD::Key::Spacebar) || input->IsButtonPressed(0, 0))
	{
		Warp();
	}

	// UI Toggle
	if (input->IsKeyPressed(SGD::Key::Tab) || input->IsButtonPressed(0, 6))
		arrowsOn = !arrowsOn;

	// Position event
	CCustomEvent* e = new CCustomEvent(EventID::position, nullptr, this);
	e->Queue();

	CEntity::Update(dt);
}

void CPlayer::Render()
{

	m_Engine->Render();

	SGD::Rectangle rShipRegion = SGD::Rectangle (SGD::Point{ 0, 0 }, size);
	
	SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
	
	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}
	
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint,rShipRegion, rotation, size / 2, col );
}

void CPlayer::AddGravity(SGD::Vector grav)
{
	if (warpTimer >= warpDuration)
		gravVec += grav;
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

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, m_shield->GetSize(), rotation, damage, laserLevel,-1.0f,this);
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
	if(wellTimer <= wellDelay)
		return;

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

void CPlayer::CreatePush()
{
	if (pushTimer <= pushDelay)
		return;

	CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerPush, false);
	pushTimer = 0;
	//TODO: Send CreatePush message
	if (pushLevel == 0)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 500, pushLevel, SGD::PI / 3, this);
		msg->QueueMessage();
	}
	else if (pushLevel == 1)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 500, pushLevel, SGD::PI / 2, this);
		msg->QueueMessage();
	}
	else if (pushLevel == 2)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 750, pushLevel, SGD::PI / 2, this);
		msg->QueueMessage();
	}
	else
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 750, pushLevel, SGD::PI * 2, this);
		msg->QueueMessage();
	}

}

void CPlayer::Warp()
{
	if (warpTimer <= warpDelay)
		return;

	CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerWarp, false);
	warpTimer = 0;
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
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::enemyShieldDamage, false);
		shield -= damage;
		damage -= shield;
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
	damaged = .15f;
	if (hull <= 0 && !destroying)
	{
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
		CSoundBox::GetInstance()->Play(CSoundBox::sounds::playerLevelUp, false);
		level++;
		perks++;
		this->exp = this->exp - expRequired;
		expRequired *= 2;
		maxShield += SHIELD_SCALE;
		maxHull += HULL_SCALE;
		shield = maxShield;
		hull = maxHull;
	}
}

void CPlayer::LaserLevelUp() 
{ 
	laserLevel++;
	if (laserLevel == 3)
		laserDelay = .15f;
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
	perks = 100;
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
		}
	}

	CShip::HandleCollision(other);
}

int CPlayer::GetTutorialPause()
{
	if (CGameplayState::GetInstance()->GetLevel() != Level::Tutorial)
		return -1;

	for (int i = 0; i < 4; i++)
	{
		if (tutorialWaitForInput[i])
			return i;
	}

	return -1;
}