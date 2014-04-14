#pragma once
#include "Trigger.h"
#include "../IEntity.h"

enum class triggerID { tutMovement, tutLasers, tutMissiles, tutWarp, tutWell, tutPush, tutArrows, tutArrowsTwo, tutCoordinator, tutHuman, tutUpgrade, tutBoss, tutStargate, finalLevel, };

class EventTrigger : public Trigger
{
	int triggerType = -1;
	bool colliding = false;

public:
	EventTrigger(){}
	~EventTrigger(){}

	int GetType() { return (int)EntityType::EventTrigger; }
	int GetTriggerType() { return triggerType; }
	void Render();

	void SetType(int _type) { triggerType = _type; }

	void HandleCollision(IEntity* other);
};

