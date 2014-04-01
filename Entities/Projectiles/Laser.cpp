#include "Laser.h"
#include "../Ships/Ship.h"
#include "../Modules/Module.h"
#include "../Collidables/Asteroid.h"
#include "../../Message System/DestroyEntityMessage.h"
#include "../../Camera.h"
#include "../../GameStates/Game.h"

CLaser::CLaser()
{

}

CLaser::~CLaser()
{

}

void CLaser::Clamp()
{
	SGD::Size world = Game::GetInstance()->GetLevelState()->GetWorldSize();
	SGD::Rectangle box = GetRect();

	//Is laser completely outside of the world?
	if (box.right < 0 || box.bottom < 0 || box.left > world.width || box.top > world.height)
	{
		//Destroy the laser
		SelfDestruct();
	}
}

void CLaser::Update(float dt)
{
	velocity += gravVec;
	gravVec = SGD::Vector{0,0};
	CEntity::Update(dt);
	if (!position.IsWithinRectangle(CCamera::GetInstance()->GetBoxInWorld()))
		SelfDestruct();
}

void CLaser::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();
	
	//Is other a ship?
	if (otherType >= EntityType::Player && otherType <= EntityType::Mamba)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		ship->TakeDamage(damage);

		//Throw a message to destroy this
		SelfDestruct();
	}
	else if (otherType >= EntityType::BaseModule && otherType <= EntityType::WarpModule)
	{
		CModule* mod = dynamic_cast<CModule*>(other);
		mod->TakeDamage(damage);

		SelfDestruct();
	}

	//Is other an asteroid?
	if (otherType == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);
		ast->TakeDamage(damage);
	}
}
