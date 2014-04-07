#include "CreateEntityMessage.h"

CreateEntityMessage::CreateEntityMessage(IEntity* creator ) : Message(MessageID::CreateEntity)
{
	sender = creator;
	sender->AddRef();
}

CreateEntityMessage::~CreateEntityMessage()
{
	sender->Release();
}