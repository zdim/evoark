#pragma once

#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"

class CVictoryMessage : public SGD::Message
{

public:
	CVictoryMessage() : SGD::Message(MessageID::Victory){}
	~CVictoryMessage(){}
};

