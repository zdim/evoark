#pragma once
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"
#include "../Entities/IEntity.h"
#include "../SGD Wrappers/SGD_Geometry.h"
class CreateProjectileMessage : public SGD::Message
{
	EntityType m_type;
	SGD::Point m_position;
	SGD::Size m_ownerSize;
	float m_rotation;
	int m_damage;
	float m_radius;
	int m_tier;
	

public:
	CreateProjectileMessage(EntityType type, SGD::Point position, SGD::Size ownerSize, float rotation, int damage, unsigned int tier, float radius = -1.0f);
	~CreateProjectileMessage(){}

	EntityType GetProjType() const {return m_type;}
	SGD::Point GetPosition()const { return m_position; }
	SGD::Size GetOwnerSize() const { return m_ownerSize; }
	float GetRotation()		const { return m_rotation; }
	int GetDamage()			const { return m_damage; }
	float GetRadius()		const { return m_radius;}
	int GetTier()			const { return m_tier; }
};