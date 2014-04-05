#pragma once
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"
#include "../Entities/IEntity.h"

class CreateEntityMessage : public SGD::Message
{
	IEntity* sender;
	EntityType toCreate;
public:
	CreateEntityMessage(IEntity* creator, EntityType created);
	~CreateEntityMessage();

	IEntity* GetSender() const {return sender;}
	EntityType GetEntityType() {return toCreate;}
};