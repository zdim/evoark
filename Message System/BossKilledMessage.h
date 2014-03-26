#pragma once

#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"

class BossKilledMessage : public SGD::Message
{
public:
	BossKilledMessage() : Message(MessageID::BossKilled) {}
	~BossKilledMessage() {}
};