//
#include "Module.h"


CModule::CModule()
{
}


CModule::~CModule()
{
}
void CModule::Update(float dt)
{
	SGD::Vector rotatedOffset = posOffset;
	rotatedOffset.Rotate(owner->GetRotation());
	position = owner->GetPosition() + rotatedOffset;
}

void CModule::TakeDamage(int damage, bool collision)
{

}

void CModule::Activate()
{

}
