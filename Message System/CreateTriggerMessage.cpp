#include "CreateTriggerMessage.h"


CreateTriggerMessage::CreateTriggerMessage(int _id) : Message(MessageID::CreateTrigger)
{
	//triggerType = (triggerID)_id;
}


CreateTriggerMessage::~CreateTriggerMessage()
{
}
