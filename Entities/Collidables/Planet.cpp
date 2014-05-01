#include "Planet.h"
#include "../Ships/Ship.h"
#include "Asteroid.h"
#include "Shield.h"
#include "ModuleShield.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

void CPlanet::Update(float dt)
{
}

void CPlanet::HandleCollision(IEntity* other)
{
	//Is the other object a ship?
	EntityType otherType = (EntityType)other->GetType();
	SGD::Vector dir = other->GetPosition() - position;
	dir.Normalize();
	if ((otherType >= EntityType::Player && otherType <= EntityType::Moccasin))
	{
		//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
		other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.5f));
	}

	if (otherType == EntityType::Shield)
	{
		CShip* owner = dynamic_cast<CShield*>(other)->GetOwner();
		owner->AddGravity(dir * (owner->getSpeed() * 3));
	}
	if (otherType == EntityType::ModuleShield)
	{
		CShip* owner = dynamic_cast<CModuleShield*>(other)->GetOwnerShip();
		owner->AddGravity(dir * (owner->getSpeed() * 3));
	}
	//Is other an asteroid?
	if (otherType == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);
		//Get the asteroid's speed
		float speed = ast->GetVelocity().ComputeLength();
		//Make a new velocity going in a different direction with the same speed
		ast->SetVelocity(dir*speed);
	}
}

void CPlanet::Render()
{
	SGD::Rectangle rShipRegion = SGD::Rectangle(SGD::Point{ 0, 0 }, size);
	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	

	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint, rShipRegion, rotation, size / 2, col);
}