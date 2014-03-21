
#include "EventManager.h"

CEventManager& CEventManager::GetInstance()
{
	static CEventManager instance;
	return instance;
}

void CEventManager::Queue(CCustomEvent* e)
{
	events.push(e);
}

void CEventManager::SendNow(CCustomEvent* e)
{
	ListenerGroup& bucket = listenerMap[e->GetID()];
	for (unsigned int i = 0; i < bucket.size(); i++)
	{
		bucket[i]->HandleEvent(e);
	}
}

void CEventManager::Register(Listener* listener, EventID id)
{
	listenerMap[id].push_back(listener);
}

void CEventManager::Unregister(Listener* listener, EventID id)
{
	unlisteners[id].push_back(listener);
}

void CEventManager::ClearEvents()
{
	while (!events.empty())
	{
		events.pop();
	}
}

void CEventManager::Update()
{
	while (!events.empty())
	{
		CCustomEvent* e = events.front();
		events.pop();
		SendNow(e);
		delete e;
	}
}
