//
#include "Well.h"

CWell::CWell()
{
	radius = size.width/2.0f;
}


CWell::~CWell()
{
}

void CWell::HandleCollision(IEntity* other)
{
	SGD::Vector dir = position - other->GetPosition();
	dir.Normalize();
	float mass = other->GetSize().width * other->GetSize().height;
	other->AddGravity(dir * mass * strength);
}