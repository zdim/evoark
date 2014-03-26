//
#include "Enemy.h"
#include "../../../Event System/EventID.h"
#include "../../../Event System/CustomEvent.h"
#include "../../../GameStates/Game.h"
#include "../../../Event System/EventManager.h"
#include "../../../Message System/CreateProjectile.h"

CEnemy::CEnemy()
{
	CEventManager::GetInstance().Register(dynamic_cast<Listener*>(this), EventID::position);
}


CEnemy::~CEnemy()
{
	CEventManager::GetInstance().Unregister(dynamic_cast<Listener*>(this), EventID::position);
}

void CEnemy::Update(float dt)
{
	if (target)
	{
		SGD::Vector tarDir = target->GetPosition() - position;
		tarDir.Normalize();
		rotateToward(tarDir, dt);
	}
}

void CEnemy::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if (target)
		target->Release();

	if (newTarget)
		newTarget->AddRef();

	target = newTarget;
}

void CEnemy::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::position:
	{
							  IEntity* other = dynamic_cast<IEntity*> (e->GetSender());
							  EntityType otherType = (EntityType)other->GetType();
							  if (otherType == EntityType::Human || otherType == EntityType::Player)
								  DetectShip(dynamic_cast<CShip*>(other));

							  //detect projectiles and collidables
							  break;							  
	}
	}
}

void CEnemy::DetectShip(CShip* other)
{
	SGD::Point pos = other->GetPosition();
	SGD::Vector toTarget = pos - position;

	SGD::Vector forward = { 0, -1 };
	forward.Rotate(rotation);
	//"delta rotation" the amount of rotation it will take to face the target.
	float angle = forward.ComputeAngle(toTarget);
	if (angle >= SGD::PI / 4.0f)
		return;

	float distance = toTarget.ComputeLength();
	if (distance >= SGD::Vector{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }.ComputeLength() * 0.25f)
		return;

	SetTarget(other);

}
