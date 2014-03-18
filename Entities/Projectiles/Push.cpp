//
#include "Push.h"


CPush::CPush()
{
	radius = SGD::PI /4.0f;
}


CPush::~CPush()
{
}

void CPush::HandleCollision(IEntity* other)
{
	SGD::Vector dir = other->GetPosition() - position;
	dir.Normalize();

	if (radius < dir.ComputeAngle(forward))
	{
		return;
	}

	float mass = other->GetSize().width * other->GetSize().height;
	other->AddGravity(dir * mass * strength);
}