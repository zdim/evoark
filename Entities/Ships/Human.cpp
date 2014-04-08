//
#include "Human.h"
#include "../../Event System/EventID.h"
#include "../../Event System/EventManager.h"
#include "../../GameStates/Game.h"
#include "../../Message System/CreateProjectile.h"
#include "../../GameStates/GameState.h"

#include <algorithm>

CHuman::CHuman()
{
	CEventManager::GetInstance().Register(this, EventID::position);
	maxHull = 2000;
	hull = maxHull;
	rescueDelay = SGD::PI * 2 / rotSpeed;
}


CHuman::~CHuman()
{
}

void CHuman::Update(float dt)
{
	if (!initial && target)
	{
		initial = true;
	}

	if (!target)
		rescueTimer+=dt;
	if (rescueTimer >= rescueDelay)
	{
		if (!rescued)
			initializeRescueAI();
		RescueAI(dt);
		return;
	}
	laserTimer += dt;

	//AI
	//Movement
	if (target)
	{
		SGD::Vector tarDir = target->GetPosition() - position;
		tarDir.Normalize();
		rotateToward(tarDir, dt);
	}
	else
	{
		SGD::Vector forward = { 0, -1 };
		forward.Rotate(rotation);
		forward.Rotate(SGD::PI / 2.1f);
		rotateToward(forward, dt);
	}

	if (target)
	{
		SGD::Vector dir = target->GetPosition() - position;
		if (dir.ComputeLength() > 100)
		{
			dir.Normalize();
			velocity = dir * speed;
		}
		else velocity = { 0, 0 };
	}
	else
	{
		velocity = { 0, 0 };
	}

	if (target)
	{
		SGD::Vector vToTarget =
		{
			GetTarget()->GetPosition().x - this->GetPosition().x,
			GetTarget()->GetPosition().y - this->GetPosition().y
		};

		SGD::Vector direction = { 0, -1 };
		direction.Rotate(rotation);
		float angle = direction.ComputeAngle(vToTarget);

		if (vToTarget.ComputeLength() <= 400 && angle < SGD::PI / 4.0f)
		{
			CreateLaser();
		}
	}

	CEntity::Update(dt);

}

void CHuman::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if (target)
		target->Release();

	target = newTarget;

	if (target)
		target->AddRef();
	else
		rescueTimer = 0;
}


void CHuman::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::position:
	{
		EntityType t = (EntityType)e->GetSender()->GetType();
		if (t >= EntityType::Copperhead && t <= EntityType::Coordinator)
		{
			DetectShip(dynamic_cast<CShip*>(e->GetSender()));
		}
	}
	}
}

void CHuman::DetectShip(CShip* other)
{
	if (!other)
		return;
	SGD::Point pos = other->GetPosition();
	SGD::Vector toTarget = pos - position;


	float distance = toTarget.ComputeLength();

	if (!initial)
	{
		if (target)
		{
			SGD::Vector toOldTarget = target->GetPosition() - position;
			float oldDistance = toOldTarget.ComputeLength();
			if (distance < oldDistance)
				SetTarget(other);
		}
		else
		{
			SetTarget(other);
		}
		return;
	}

	SGD::Vector forward = { 0, -1 };
	forward.Rotate(rotation);
	//"delta rotation" the amount of rotation it will take to face the target.
	float angle = forward.ComputeAngle(toTarget);
	if (angle >= SGD::PI / 4.0f)
		return;

	if (distance >= SGD::Vector{ (float)Game::GetInstance()->GetScreenWidth() * 0.5f, (float)Game::GetInstance()->GetScreenHeight() * 0.5f }.ComputeLength())
	{
		//if (other == target)
		//	SetTarget(nullptr);
		return;
	}
	SetTarget(other);
	//if (leader)
	//	leader->SetTarget(other);
}

void CHuman::CreateLaser()
{
	if (laserTimer >= laserDelay)
	{
		CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size * 1.5f, rotation, damage, 0, -1, this);
		msg->QueueMessage();
		laserTimer = 0;
	}
}

void CHuman::initializeRescueAI()
{
	rescued = true;
	SGD::Size worldsize = Game::GetInstance()->GetLevelState()->GetWorldSize();

	float leftDist = position.x;
	float topDist = position.y;
	float rightDist = abs(worldsize.width - position.x);
	float bottomDist = abs(worldsize.height - position.y);

	float smallest = std::min(leftDist, std::min(topDist, std::min(rightDist, bottomDist)));

	if (smallest == leftDist)
		velocity = SGD::Vector{ -1, 0 } *speed;
	else if (smallest == topDist)
		velocity = SGD::Vector{ 0, -1 } *speed;
	else if (smallest == rightDist)
		velocity = SGD::Vector{ 1, 0 } * speed;
	else
		velocity = SGD::Vector{ 0, 1 } * speed;
}

void CHuman::RescueAI(float dt)
{
	rotateToward(velocity,dt);
	CEntity::Update(dt);
	if (!CCamera::GetInstance()->GetBoxInWorld().IsIntersecting(GetRect()))
	{
		SelfDestruct();
	}
}