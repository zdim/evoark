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

#define SHIELD_SCALE 100
#define HULL_SCALE 200

CPlayer::CPlayer()
{
	maxShield = 500;
	shield = maxShield;
	shieldRegen = 500;
	shieldDelay = 2;
	shieldTimer = laserTimer = missileTimer = wellTimer = pushTimer = warpTimer = 20;
	laserDelay = 0.25f;
	missileDelay = 2.0f;
	wellDelay = 5;
	pushDelay = 10;
	warpDelay = 10;
	warpSpeed = 500;
	exp = 0;
	expRequired = 100;
	level = 0;

	wellIcon = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/GravWellIcon.png");
	pushIcon = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/GravPushIcon.png");
	warpIcon = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/WarpIcon.png");
}


CPlayer::~CPlayer()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(wellIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(pushIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(warpIcon);
}

void CPlayer::Update(float dt)
{
	//Timers
	shieldTimer += dt;
	laserTimer += dt;
	missileTimer += dt;
	wellTimer += dt;
	pushTimer += dt;
	warpTimer += dt;


	CParticleSystem::GetInstance()->GetParticleEffect(1)->SetEmitterPosition(position);

	CParticleSystem::GetInstance()->GetParticleEffect(1)->Update(dt);



	if (shieldTimer >= shieldDelay)
	{
		shield += int(shieldRegen * dt);
		if (shield > maxShield)
			shield = maxShield;
	}

	//Movement
	SGD::InputManager* input = SGD::InputManager::GetInstance();
	SGD::Vector dir = SGD::Vector{0,0};
	if (input->IsKeyDown(SGD::Key::W))
		dir.y -= 1;
	if (input->IsKeyDown(SGD::Key::S))
		dir.y += 1;
	if (input->IsKeyDown(SGD::Key::A))
		dir.x -= 1;
	if (input->IsKeyDown(SGD::Key::D))
		dir.x += 1;
	if (dir != SGD::Vector{0, 0})
		dir.Normalize();
	 //commented out until finished implementing - was messing up standard input
	if (warpTimer < warpDuration)
		velocity = dir * (speed + warpSpeed);
	else
		velocity = dir * speed;
	SGD::Point mousePos = input->GetMousePosition();
	rotation = atan2(mousePos.y - offsetToCamera().y, mousePos.x - offsetToCamera().x) + SGD::PI / 2;

	

	//Abilities
	if (input->IsKeyDown(SGD::Key::LButton))
	{
		CreateLaser();
	}
	if (input->IsKeyDown(SGD::Key::RButton))
	{
		CreateMissile();
	}
	if (input->IsKeyPressed(SGD::Key::Q))
	{
		CreateWell();
	}
	if (input->IsKeyPressed(SGD::Key::E))
	{
		CreatePush();
	}
	if (input->IsKeyPressed(SGD::Key::Spacebar))
	{
		Warp();
	}

	// UI Toggle
	if (input->IsKeyPressed(SGD::Key::Tab))
		arrowsOn = !arrowsOn;

	// Position event
	CCustomEvent* e = new CCustomEvent(EventID::position, nullptr, this);
	e->Queue();

	CEntity::Update(dt);

	
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

	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size, rotation, damage, laserLevel);
	msg->QueueMessage();
}

void CPlayer::CreateMissile()
{
	if (missileTimer <= missileDelay)
		return;
	missileTimer = 0;
	//TODO: Send CreateMissile message
	int damage = 75;
	damage *= int(1.5f * missileLevel);
	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Missile, position, size, rotation, damage, missileLevel );
	msg->QueueMessage();
}

void CPlayer::CreateWell()
{
	if(wellTimer <= wellDelay)
		return;
	wellTimer = 0;
	//TODO: Send CreateWell message
	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Well, SGD::InputManager::GetInstance()->GetMousePosition() - CCamera::GetInstance()->GetOffset(), size, rotation, 150, wellLevel, 128);
	msg->QueueMessage();
}

void CPlayer::CreatePush()
{
	if (pushTimer <= pushDelay)
		return;
	pushTimer = 0;
	//TODO: Send CreatePush message
	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Push, position, size, rotation, 500, pushLevel, SGD::PI / 4);
	msg->QueueMessage();
}

void CPlayer::Warp()
{
	if (warpTimer <= warpDelay)
		return;


	warpTimer = 0;
}

void CPlayer::TakeDamage(int damage, bool collision)
{
	if (collision && warpTimer <= warpDuration && warpLevel >= 3)
	{
		return;
	}
	if (collision)
		damage *= COLLISION_MODIFIER;
	shieldTimer = 0;
	if (shield > 0)
	{
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

	hull -= damage;
	if (hull <= 0 && !destroying)
	{
		CCreateGameOverMessage* msg = new CCreateGameOverMessage();
		msg->QueueMessage();
		SelfDestruct();
	}
}

void CPlayer::Render()
{
	if (shield > 0)
		CParticleSystem::GetInstance()->GetParticleEffect(1)->Render();
	SGD::Color color = {};
	if (shield < maxShield)
		color = SGD::Color{ 255, 0, 0 };
	float scale = std::max(size.width / imageSize.width, size.height / imageSize.height);
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, offsetToCamera(), rotation, imageSize / 2, color, { scale, scale });
}

void CPlayer::AddExp(int _exp)
{
	this->exp += _exp;
	if (this->exp >= expRequired)
	{
		level++;
		this->exp = this->exp - expRequired;
		expRequired *= 2;
		maxShield += SHIELD_SCALE;
		maxHull += HULL_SCALE;
		shield = maxShield;
		hull = maxHull;
	}
}