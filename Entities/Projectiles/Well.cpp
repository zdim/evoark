//
#include "Well.h"

CWell::CWell()
{
	radius = size.width/2.0f;
	duration = 3;
}


CWell::~CWell()
{
}

void CWell::HandleCollision(IEntity* other)
{
	SGD::Vector dir = position - other->GetPosition();
	dir.Normalize();
	//float mass = other->GetSize().width * other->GetSize().height;
	other->AddGravity(dir * strength);
}