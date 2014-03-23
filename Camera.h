#pragma once
#include "SGD Wrappers\SGD_Geometry.h"
#include "Entities\IEntity.h"
class CCamera
{
	SGD::Point pos;
	SGD::Size screenSize;
	IEntity* target;
	float speed = 250;
public:
	CCamera(IEntity* t, SGD::Size screen);
	~CCamera();

	void Update(float dt);
	SGD::Rectangle GetBoxInWorld() { return SGD::Rectangle(pos, screenSize); }
	float GetSpeed() {return speed;}
	void SetSpeed(float s) {speed = s;}
	void SetTarget(IEntity* t);
	SGD::Vector GetOffset() {return SGD::Point{0,0} - pos;}
	void SetScreenSize(SGD::Size newsize) {screenSize = newsize;}
};
