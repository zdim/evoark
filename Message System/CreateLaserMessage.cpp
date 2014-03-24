#include "CreateLaserMessage.h"

CreateLaserMessage::CreateLaserMessage(SGD::Point position, SGD::Size ownerSize, float rotation, int damage, bool boostDamageAgainstShield) : Message(MessageID::CreateLaser)
{
	m_position = position;
	m_size = ownerSize;
	m_rotation = rotation;
	m_damage = damage;
	m_boost = boostDamageAgainstShield;
}
