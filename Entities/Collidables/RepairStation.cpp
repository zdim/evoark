#include "RepairStation.h"
#include "../Ships/Ship.h"
#include "Asteroid.h"
#include "../Ships/Enemies/Moccasin.h"
#include "../Projectiles/Laser.h"
#include "../../Event System/EventID.h"
#include "../../Event System/CustomEvent.h"
#include "../../Event System/EventManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

CRepairStation::CRepairStation()
{
	hull = 100;
	size = { 92, 217 };
	CEventManager::GetInstance().Register(dynamic_cast<Listener*>(this), EventID::bossdead);
}



void CRepairStation::Update(float dt)
{
	if (m_pOwner != nullptr)
	{

		for (int i = 0; i != m_pOwner->GetModules().size(); ++i)
		{
			if (m_pOwner->GetModules()[i] != nullptr)
			{
				int test = m_pOwner->GetModules()[i]->GetHull();
				int test2 = m_pOwner->GetModules()[i]->GetHullMax();

				if (m_pOwner->GetModules()[i]->GetHull() < m_pOwner->GetModules()[i]->GetHullMax())
				{
					int heal = m_pOwner->GetModules()[i]->GetHull() + 1;
					if (heal > m_pOwner->GetModules()[i]->GetHullMax())
						m_pOwner->GetModules()[i]->SetHull(m_pOwner->GetModules()[i]->GetHullMax());
					else
						m_pOwner->GetModules()[i]->SetHull(heal);

				}

			}

		}
	}


}



void CRepairStation::Render()
{
	SGD::Rectangle rShipRegion = SGD::Rectangle(SGD::Point{ 0, 0 }, size);

	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}

	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint, rShipRegion, rotation, size / 2, col);
}

void CRepairStation::HandleCollision(IEntity* other)
{
	//Is the other object a ship?




	EntityType otherType = (EntityType)other->GetType();


	if (otherType == EntityType::Laser || otherType == EntityType::Missile)
	{
		dynamic_cast<CLaser*>(other)->HandleCollision(this);
		//other->HandleCollision(dynamic_cast<CShieldModule*>(m_pOwner));

	}


	SGD::Vector dir = other->GetPosition() - position;
	dir.Normalize();

	if (otherType >= EntityType::Player && otherType <= EntityType::Moccasin)
	{
		//This formula gets the direction from us to them (so away from us), then multiplies that by (their speed * 1.1) so that they can only fight the push from impact a little bit
		other->AddGravity(dir * (dynamic_cast<CShip*>(other)->getSpeed() * 1.1));
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

void CRepairStation::TakeDamage(int damage)
{
	hull -= damage;
	if (hull <= 0)
	{
		SelfDestruct();
	}
}

void CRepairStation::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::bossdead:
	{
							  SetOwner(nullptr);
							  break;
	}
	}
}
