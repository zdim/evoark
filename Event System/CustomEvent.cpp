
#include "CustomEvent.h"


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

