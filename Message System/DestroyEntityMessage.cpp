#include "DestroyEntityMessage.h"

DestroyEntityMessage::DestroyEntityMessage(IEntity* toDestroy) : Message(MessageID::DestroyEntity)
{
	sender = toDestroy;
	sender->AddRef();
}

DestroyEntityMessage::~DestroyEntityMessage()
{
	sender->Release();
}