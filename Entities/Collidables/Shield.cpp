#include "Shield.h"
#include "../Ships/Ship.h"
#include "Asteroid.h"
#include "../Projectiles/Laser.h"
#include "../Ships/Player.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

void CShield::Update(float dt)
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->GetShield() > 0)
	{
		position = m_pOwner->GetPosition();
		//Doesn't really do anything in this context.
		//CEntity::Update(dt);
	}	
}

void CShield::HandleCollision(IEntity* other)
{
	//Is the other object a ship?
	if (dynamic_cast<CPlayer*>(m_pOwner)->GetShield() > 0)
	{
		EntityType otherType = (EntityType)other->GetType();
		SGD::Vector dir = other->GetPosition() - position;




		if (otherType != EntityType::Player)
		{
			(m_pOwner)->HandleCollision(other);
			other->HandleCollision(m_pOwner);



			//dir.Normalize();
			//if (otherType >= EntityType::Copperhead && otherType <= EntityType::Moccasin)
			//{
			//	//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
			//	other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1));
			//}
		}

		//if (otherType == EntityType::Laser)
		//{
		//	CLaser* ast = dynamic_cast<CLaser*>(other);
		//	//Get the asteroid's speed
		//	ast->SelfDestruct();

		//	//SGD::Vector dir = other->GetPosition() - position;
		//	//dir.Normalize();
		//	//other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1));
		//	////Have the other ship take damage based on our mass and speed (not necessarily our current speed/velocity)
		//	////We will probably rebalance this later.
		//	//float mass = size.width * size.height / 100;


		//	m_pOwner->TakeDamage(ast->GetDamage(), false);
		}
		//Is other an asteroid?
	
		
}

void CShield::Render()
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->GetShield() > 0)
	{
		SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
		//CCamera* cam = Game::GetInstance()->GetLevelState()->GetCam();
		//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
		SGD::Point renderPoint = offsetToCamera();
		//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint,SGD::Rectangle{SGD::Point{0,0}, imageSize}, rotation, imageSize/2, {}, scale);

		SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, {}, scale);
	}
}