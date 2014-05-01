#pragma once
#include "Stationary.h"
#include "../../Message System/MessageID.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../EntityManager.h"

class Trigger : public Stationary
{
	SGD::Message* Message = nullptr;
public:
	Trigger(){}
	~Trigger(){if(Message) delete Message;}
	SGD::Size GetSize() {return size * 0.9f;}
	int GetType() { return (int)EntityType::Stargate; }
	virtual MessageID GetID() {return Message->GetMessageID();}
	virtual void HandleCollision(IEntity* other) 
	{ 
		if (other->GetType() == (int)EntityType::Player && Message && CEntityManager::GetInstance()->GetBoss() == nullptr) 
		{
			Message->QueueMessage(); 
			Message = nullptr;
			CEntityManager::GetInstance()->SpawnProjectile(EntityType::Well, position, size, 0.0f, 1000, 1, size.width * 0.5f,this); 
		}
		EntityType otherType = (EntityType)other->GetType();
		if (!Message && (otherType == EntityType::Asteroid || otherType == EntityType::Laser || otherType == EntityType::Missile || (otherType > EntityType::Player && otherType <= EntityType::Moccasin)))
		{
			other->SelfDestruct();
		}
	}
	void Assign(SGD::Message* msg) {Message = msg;}
};