#include "Stationary.h"
#include "../../Message System/MessageID.h"

class Trigger : public Stationary
{
	MessageID ID;
public:
	virtual MessageID GetID() {return ID;}
	void Render(){}
	void HandleCollision(IEntity* other);
};