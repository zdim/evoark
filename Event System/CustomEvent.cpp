
#include "CustomEvent.h"
#include "EventManager.h"

CCustomEvent::CCustomEvent(EventID t, void* d, IEntity* s)
{
	type = t;
	data = d;
	sender = s;
	sender->AddRef();
}


CCustomEvent::~CCustomEvent()
{
	sender->Release();
}

void CCustomEvent::Queue()
{
	CEventManager::GetInstance().Queue(this);
}