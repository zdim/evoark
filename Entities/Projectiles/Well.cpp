//
#include "Well.h"
#include "../Collidables/Asteroid.h"
#include "../Ships/Ship.h"
#include "../Modules/Module.h"


CWell::CWell()
{
	radius = size.width/2.0f;
	duration = 3;
}


CWell::~CWell()
{
}

//void CWell::Update(float dt)
//{
//	if (duration - timer < 0.1)
//	{
//
//	}
//}

void CWell::Render()
{

}



void CWell::HandleCollision(IEntity* other)
{	
	SGD::Vector dir;
	if ( tier >= 3 && (duration - timer) < 0.1f)
	{
		dir = other->GetPosition() - position;
		dir.Normalize();
		other->AddGravity(dir * strength * 2);
		EntityType type = (EntityType)other->GetType();
		if (type == EntityType::Asteroid)
		{
			CAsteroid* ast = dynamic_cast<CAsteroid*>(other);
			ast->TakeDamage(int(strength * 0.075f));
		}
		else if (type >= EntityType::Player && type <= EntityType::Coordinator)
		{
			CShip* ship = dynamic_cast<CShip*>(other);
			ship->TakeDamage(int(strength * 0.075f));
		}
		else if (type >= EntityType::BaseModule && type <= EntityType::WarpModule)
		{
			CModule* mod = dynamic_cast<CModule*>(other);
			mod->TakeDamage(int(strength * 0.075f));
		}
		return;
	}
	dir = position - other->GetPosition();
	if (dir.ComputeLength() < 1)
		dir.y += 1;
	dir.Normalize();
	//float mass = other->GetSize().width * other->GetSize().height;
	other->AddGravity(dir * strength);
}