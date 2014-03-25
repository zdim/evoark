#pragma once
#include "Stationary.h"
#include "../../Message System/MessageID.h"
#include "../../SGD Wrappers/SGD_Message.h"

class Trigger : public Stationary
{
	SGD::Message* Message = nullptr;
public:
	Trigger(){}
	~Trigger(){if(Message) delete Message;}
	int GetType() { return (int)EntityType::Stargate; }
	virtual MessageID GetID() {return Message->GetMessageID();}
	void HandleCollision(IEntity* other) { if (other->GetType() == (int)EntityType::Player) {Message->QueueMessage(); Message = nullptr; }}
	void Assign(SGD::Message* msg) {Message = msg;}
};