#pragma once
#include "CustomEvent.h"
#include <queue>
#include <map>
#include "IListener.h"
#include "EventID.h"
class CEventManager
{
	std::queue<CCustomEvent*> events;
	static CEventManager instance;
	typedef std::vector<Listener*> ListenerGroup;
	std::map<EventID, ListenerGroup> listenerMap;
	std::map<EventID, ListenerGroup> unlisteners;
	CEventManager() = default;
	~CEventManager() = default;

public:
	static CEventManager& GetInstance();
	void Queue(CCustomEvent* e);
	void SendNow(CCustomEvent* e);
	void Register(Listener* listener, EventID id);
	void Unregister(Listener* listener, EventID id);
	void ClearEvents();
	void ClearListeners();

	void Update();
};

