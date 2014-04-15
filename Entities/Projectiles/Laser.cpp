#include "Laser.h"
#include "../Ships/Ship.h"
#include "../Modules/Module.h"
#include "../Collidables/Asteroid.h"
#include "../../Message System/DestroyEntityMessage.h"
#include "../../Camera.h"
#include "../../GameStates/Game.h"
#include "../Collidables/ModuleShield.h"
#include "../Collidables/RepairStation.h"
#include "../../Event System/CustomEvent.h"
#include "../../Event System/EventID.h"
#include "../../SGD Wrappers/SGD_Color.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


CLaser::CLaser()
{
	
	size = { 8, 18 };

	
}

CLaser::~CLaser()
{
	SetOwner(nullptr);
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
	CCustomEvent* e = new CCustomEvent(EventID::position, nullptr, this);
	e->Queue();
}

void CLaser::Render()
{
	SGD::Color col = { 0, 0, 0 };
	switch (tier)
	{
	case 0:
		col = { 200, 20, 20 };
		break;
	case 1:
		col = { 200, 200, 20 };
		break;
	case 2:
		col = { 200, 20, 200 };
		break;
	case 3:
		col = { 20, 200, 20 };
		break;
	}
	SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
	SGD::Point renderPoint = offsetToCamera();

	SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize * .5f, col, scale);
	//CProjectile::Render();
}

void CLaser::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();
	
	//Is other a ship?
	if (otherType >= EntityType::Player && otherType <= EntityType::Mamba)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		
	
			if (this->GetOwner()->GetType() == (int)EntityType::Player)
			{
				ship->TakeDamage(damage);
			}
			else if (this->GetOwner()->GetType() != (int)EntityType::Player && ship->GetType() == (int)EntityType::Player)
			{
				
				ship->TakeDamage(damage);
			}
		
		
		SelfDestruct();
		//Throw a message to destroy this
		
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
		SelfDestruct();
	}

	if (otherType == EntityType::RepairStation)
	{
		CRepairStation* st = dynamic_cast<CRepairStation*>(other);
		st->TakeDamage(damage);
		SelfDestruct();
	}

	//Is other a planet
	if (otherType == EntityType::Planet)
	{
		SelfDestruct();
	}

}

void CLaser::AddGravity(SGD::Vector grav)
{
	float speed = velocity.ComputeLength();
	grav.Normalize();
	SGD::Vector dir = velocity;
	dir.Normalize();
	float angle = dir.ComputeAngle(grav);
	angle *= dir.ComputeSteering(grav);
	angle *= 0.5f;
	dir.Rotate(angle);
	velocity = dir * speed;
	SGD::Vector forward = {0,-1};
	rotation = forward.ComputeAngle(dir);
}

void CLaser::SetOwner(IEntity* _owner)
{
	if (owner)
		owner->Release();

	owner = _owner;

	if (owner)
		owner->AddRef();
}