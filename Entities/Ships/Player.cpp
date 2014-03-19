//
#include "Player.h"
#include <math.h>
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include <algorithm>

CPlayer::CPlayer()
{
	maxShield = 500;
	shield = maxShield;
	shieldRegen = 500;
	shieldDelay = 2;

}


CPlayer::~CPlayer()
{
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
	// commented out until finished implementing - was messing up standard input
	/*if (warpTimer <= warpDuration)
	{
		velocity = dir * (speed + warpSpeed);
	}
	else
	{
		velocity = dir *speed;
	}*/
	velocity = dir * speed;
	SGD::Point mousePos = input->GetMousePosition();
	rotation = atan2(mousePos.y - position.y, mousePos.x - position.x) + SGD::PI / 2;
	CEntity::Update(dt);

	//Abilities
	if (input->IsKeyPressed(SGD::Key::LButton))
	{
		CreateLaser();
	}
	if (input->IsKeyPressed(SGD::Key::RButton))
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

}

void CPlayer::CreateMissile()
{
	if (missileTimer <= missileDelay)
		return;
	missileTimer = 0;
	//TODO: Send CreateMissile message

}

void CPlayer::CreateWell()
{
	if(wellTimer <= wellDelay)
		return;
	wellTimer = 0;
	//TODO: Send CreateWell message

}

void CPlayer::CreatePush()
{
	if (pushTimer <= pushDelay)
		return;
	pushTimer = 0;
	//TODO: Send CreatePush message

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
	shieldTimer = 0;
	if (shield > 0)
	{
		shield -= damage;
		damage -= shield;
	}

	if (damage <= 0)
	{
		return;
	}

	hull -= damage;
	if (hull <= 0)
	{
		//Send gameOver message
	}
}

void CPlayer::Render()
{
	SGD::Color color = {};
	if (shield < maxShield)
		color = SGD::Color{ 255, 0, 0 };
	float scale = std::max(size.width / imageSize.width, size.height / imageSize.height);
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, position - size / 2, rotation, imageSize / 2, color, { scale, scale });
}