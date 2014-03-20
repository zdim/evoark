#include "CreateLaserMessage.h"

CreateLaserMessage::CreateLaserMessage(SGD::Point position, float rotation, int damage, bool boostDamageAgainstShield) : Message(MessageID::CreateLaser)
{
	m_position = position;
	m_rotation = rotation;
	m_damage = damage;
	m_boost = boostDamageAgainstShield;
}
