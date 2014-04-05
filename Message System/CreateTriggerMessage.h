#pragma once
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"

//enum class triggerID { tutMovement, tutLasers, tutMissiles, tutWarp, tutWell, tutPush, tutCoordinator, tutHuman, tutBoss, };

class CreateTriggerMessage : public SGD::Message
{
	
	//triggerID triggerType;

public:
	CreateTriggerMessage(int _trigger);
	virtual ~CreateTriggerMessage();

	//int GetTriggerType() const { return (int)triggerType; }
};

