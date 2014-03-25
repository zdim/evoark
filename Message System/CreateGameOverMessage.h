#pragma once
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"


class CCreateGameOverMessage : public SGD::Message
{

public:
	CCreateGameOverMessage();
	~CCreateGameOverMessage();
};

