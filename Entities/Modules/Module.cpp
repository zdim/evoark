//
#include "Module.h"
#include "../Ships/Enemies/Coral.h"

CModule::CModule()
{
	owner = nullptr;
}


CModule::~CModule()
{
}

void CModule::SetOwner(CCoral* newVal)
{
	if (owner == newVal)
		return;

	if (owner)
		owner->Release();

	owner = newVal;

	if (owner)
		owner->AddRef();
}

void CModule::Update(float dt)
{
	timer += dt;
	SGD::Vector rotatedOffset = posOffset;
	rotatedOffset.Rotate(owner->GetRotation());
	position = owner->GetPosition() + rotatedOffset;

	rotation = owner->GetRotation() + rotOffset;
}

void CModule::TakeDamage(int damage, bool collision)
{
	damage -= owner->RequestShield(damage);
	if (collision)
		damage *= COLLISION_MODIFIER;
	hull -= damage;
	if (hull <= 0)
	{
		SelfDestruct();
	}
}

void CModule::Activate()
{

}

void CModule::ReleaseOwner()
{
	if (!owner)
		return;
	owner->Release();
}

void CModule::SelfDestruct()
{
	owner->DestroyModule(this);
}