#include "Asteroid.h"
#include "../Ships\Ship.h"
#include "../Modules/ShieldModule.h"

#include "../../Message System/DestroyEntityMessage.h"
#include "../../GameStates/Game.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

void CAsteroid::TakeDamage(int damage)
{
	health -= damage;
	damaged = .15f; 
	if (health <= 0)
	{
		
		SelfDestruct();
	}
}

void CAsteroid::Clamp()
{
	SGD::Size world = Game::GetInstance()->GetLevelState()->GetWorldSize();
	SGD::Rectangle box = GetRect();

	if (box.right < 0)
	{
		position.x = world.width + size.width/2;
	}

	if (box.bottom < 0)
	{
		position.y = world.height + size.height / 2;
	}

	if (box.left > world.width)
	{
		position.x = 0 - size.width / 2;
	}

	if (box.top > world.height)
	{
		position.y = 0 - size.height / 2;
	}
}

void CAsteroid::Update(float dt)
{
	if (velocity.ComputeLength() > speed)
		velocity -= velocity * GRAVDECAY;
	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;
	CEntity::Update(dt);
}

void CAsteroid::Render()
{
	SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
	//CCamera* cam = Game::GetInstance()->GetLevelState()->GetCam();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
	SGD::Point renderPoint = offsetToCamera();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint,SGD::Rectangle{SGD::Point{0,0}, imageSize}, rotation, imageSize/2, {}, scale);
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, col, scale);
}

void CAsteroid::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();

	//Is other a ship?
	if (otherType >= EntityType::ShieldModule || otherType >= EntityType::Shield)
	{

		SelfDestruct();
	}


	if (otherType >= EntityType::Player && otherType <= EntityType::Coordinator)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		//Have them take damage based on our size and velocity

		float mass = (size.width * size.height) / 10;

		ship->TakeDamage(int(mass * speed), true);

		//Have them recieve a force based on our directions and their max speed
		SGD::Vector dir = ship->GetPosition() - position;
		dir.Normalize();
		ship->AddGravity(dir * ship->getSpeed() * 0.5f);
	}

	//Is the other an asteroid?
	if (otherType == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);

		//Have it take damage based on our mass and velocity

		float mass = size.width * size.height / 100;
		float speed = velocity.ComputeLength();
		ast->TakeDamage(int(mass*speed));

		//Apply a force based on our directions and their current speed
		SGD::Vector dir = ast->GetPosition() - position;
		dir.Normalize();
		ast->AddGravity(dir * ast->GetSpeed());
	}
}

void CAsteroid::AddGravity(SGD::Vector grav)
{
	velocity += grav;
}
