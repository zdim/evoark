
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
		unsigned int j;
		for (j = 0; j < unlisteners[e->GetID()].size(); j++)
		{
			if (bucket[i] == unlisteners[e->GetID()][j])
				break;
		}
		if (j == unlisteners[e->GetID()].size())
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

void CEventManager::ClearListeners()
{
	listenerMap.clear();
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
	for (unsigned int i = 0; i < unlisteners.size(); i++)
	{
		while (!unlisteners[(EventID)i].empty())
		{
			Listener* ent = unlisteners[(EventID)i].back();
			for (unsigned int j = 0; j < listenerMap[(EventID)i].size(); j++)
			{
				if (listenerMap[(EventID)i][j] == ent)
				{
					listenerMap[(EventID)i].erase(listenerMap[(EventID)i].begin() + j);
					unlisteners[(EventID)i].pop_back();
					break;
				}
			}
		}
	}
}
