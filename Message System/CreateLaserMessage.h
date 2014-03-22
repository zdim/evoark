#pragma once
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"
#include "../Entities/IEntity.h"
#include "../SGD Wrappers/SGD_Geometry.h"
class CreateLaserMessage : public SGD::Message
{
	SGD::Point m_position;
	float m_rotation;
	int m_damage;
	bool m_boost;
public:
	CreateLaserMessage(SGD::Point position, float rotation, int damage, bool boostDamageAgainstShield = false);
	~CreateLaserMessage(){}

	SGD::Point GetPosition()const {return m_position;}
	float GetRotation()		const {return m_rotation;}
	int GetDamage()			const {return m_damage;}
	bool GetBoost()			const {return m_boost;}
};