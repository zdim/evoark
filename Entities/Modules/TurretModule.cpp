//
#include "TurretModule.h"
#include "../../Message System/CreateProjectile.h"

CTurretModule::CTurretModule()
{
	target = nullptr;
}


CTurretModule::~CTurretModule()
{
}

void CTurretModule::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if (target)
		target->Release();

	target = newTarget;

	if (target)
		target->AddRef();
}

void  CTurretModule::Update(float dt)
{
	CModule::Update(dt);
	//Rotate toward target
	if (target)
	{
		SGD::Vector toTarget = target->GetPosition() - position;
		CEntity::rotateToward(toTarget, dt);

		SGD::Vector forward = {0,-1};
		forward.Rotate(rotation);
	}
}
