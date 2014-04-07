//
#include "Human.h"
#include "../../Event System/EventID.h"
#include "../../Event System/EventManager.h"
#include "../../GameStates/Game.h"
#include "../../Message System/CreateProjectile.h"0

CHuman::CHuman()
{
	CEventManager::GetInstance().Register(this, EventID::position);
	maxHull = 2000;
	hull = maxHull;
}


CHuman::~CHuman()
{
}

void CHuman::Update(float dt)
{
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
	if (target)
		target->Release();

	target = newTarget;

	if (target)
		target->AddRef();
}


void CHuman::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::position:
	{
		EntityType t = (EntityType)e->GetSender()->GetType();
		if (t >= EntityType::Copperhead || t <= EntityType::Coordinator)
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

	SGD::Vector forward = { 0, -1 };
	forward.Rotate(rotation);
	//"delta rotation" the amount of rotation it will take to face the target.
	float angle = forward.ComputeAngle(toTarget);
	if (angle >= SGD::PI / 4.0f)
		return;

	float distance = toTarget.ComputeLength();
	if (distance >= SGD::Vector{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }.ComputeLength())
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
	CreateProjectileMessage* msg = new CreateProjectileMessage(EntityType::Laser, position, size, rotation, damage);
	msg->QueueMessage();
}