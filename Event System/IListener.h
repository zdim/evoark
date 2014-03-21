#pragma once
#include "CustomEvent.h"

class Listener
{
public:
	virtual void HandleEvent(CCustomEvent* e);
};