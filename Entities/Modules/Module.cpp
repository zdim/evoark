//
#include "Module.h"


CModule::CModule()
{
	owner = nullptr;
}


CModule::~CModule()
{
}

void CModule::SetOwner(IEntity* newVal)
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
	SGD::Vector rotatedOffset = posOffset;
	rotatedOffset.Rotate(owner->GetRotation());
	position = owner->GetPosition() + rotatedOffset;

	rotation = owner->GetRotation() + rotOffset;
}

void CModule::TakeDamage(int damage, bool collision)
{
	hull -= damage;
	if (hull <= 0)
	{
		//Destroy thing
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