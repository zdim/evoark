#include "CreateProjectile.h"

CreateProjectileMessage::CreateProjectileMessage(EntityType type, SGD::Point position, SGD::Size ownerSize, float rotation, int damage, unsigned int tier, float radius) : Message(MessageID::CreateProjectile)
{
	m_type = type;
	m_position = position;
	m_ownerSize = ownerSize;
	m_rotation = rotation;
	m_damage = damage;
	m_tier = tier;
	m_radius = radius;
}

