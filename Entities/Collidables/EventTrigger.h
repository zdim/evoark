#pragma once
#include "Trigger.h"
#include "../IEntity.h"

enum class triggerID { tutMovement, tutLasers, tutMissiles, tutWarp, tutWell, tutPush, tutCoordinator, tutHuman, tutBoss, };

class EventTrigger : public Trigger
{
	int triggerType = -1;
	bool colliding = false;

public:
	EventTrigger(int _type);
	virtual ~EventTrigger();

	void Render();

	void HandleCollision(IEntity* other);
};

