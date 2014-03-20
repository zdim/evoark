#include "CreateEntityMessage.h"

CreateEntityMessage::CreateEntityMessage(IEntity* creator, EntityType created) : Message(MessageID::CreateEntity)
{
	sender = creator;
	toCreate = created;
	sender->AddRef();
}

CreateEntityMessage::~CreateEntityMessage()
{
	sender->Release();
}