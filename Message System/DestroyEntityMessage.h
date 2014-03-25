#pragma once
#include "../SGD Wrappers/SGD_Message.h"
#include "../Entities/IEntity.h"
#include "MessageID.h"

class DestroyEntityMessage : public SGD::Message
{
	IEntity* sender = nullptr;
public:
	IEntity* GetEntity() const {return sender;}
	DestroyEntityMessage(IEntity* toDestroy);
	~DestroyEntityMessage();
};