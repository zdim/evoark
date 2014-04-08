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
	}	
}

void CShield::HandleCollision(IEntity* other)
{
	if (other == m_pOwner)
		return;
	//Is the other object a ship?
	if (dynamic_cast<CPlayer*>(m_pOwner)->GetShield() > 0)
	{
		EntityType otherType = (EntityType)other->GetType();
		SGD::Vector dir = other->GetPosition() - position;




		if (otherType != EntityType::Player)
		{
			(m_pOwner)->HandleCollision(other);
   			other->HandleCollision(m_pOwner);
		}

	}
		
}

void CShield::Render()
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->GetShield() > 0)
	{
		SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
		SGD::Point renderPoint = offsetToCamera();
		SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, {}, scale);
	}
}