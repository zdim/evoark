//
#include "Player.h"
#include "../../SGD Wrappers/SGD_InputManager.h"

CPlayer::CPlayer()
{
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
	dir.Normalize();
	if (warpTimer <= warpDuration)
	{
		velocity = dir * (speed + warpSpeed);
	}
	else
	{
		velocity = dir *speed;
	}
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