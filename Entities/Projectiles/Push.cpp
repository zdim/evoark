//
#include "Push.h"


CPush::CPush()
{
	radius = SGD::PI /4.0f;
	duration = 0.2;
	size = {512,512};
}


CPush::~CPush()
{
}

void CPush::Render()
{
	
}


void CPush::SetOwner(IEntity* _owner)
{
	if (owner)
		owner->Release();

	owner = _owner;

	if (owner)
		owner->AddRef();
}

void CPush::HandleCollision(IEntity* other)
{
	if (other == owner)
		return;
	SGD::Vector forward = {0,-1};
	forward.Rotate(rotation);
	SGD::Vector dir = other->GetPosition() - position;
	dir.Normalize();
	float angleBetween = dir.ComputeAngle(forward);
	if (radius < dir.ComputeAngle(forward))
	{
		return;
	}
	if (radius < SGD::PI * 2)
		dir.Rotate(angleBetween / 2);

	//float mass = other->GetSize().width * other->GetSize().height;
	other->AddGravity(dir * strength);
}