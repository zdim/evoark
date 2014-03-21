#pragma once
#include "EventID.h"
#include "../Entities/IEntity.h"
class CCustomEvent
{
	EventID type;
	void* data;
	IEntity* sender;
public:
	CCustomEvent(EventID t, void* d = nullptr, IEntity* s = nullptr);
	virtual ~CCustomEvent();

	void Queue();
	void SendNow();
	EventID GetID() {return type;}
};

