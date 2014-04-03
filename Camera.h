#pragma once
#include "SGD Wrappers\SGD_Geometry.h"
#include "Entities\IEntity.h"
class CCamera
{
	enum camState {unitiallized, initiallized, terminated};
	camState state;
	SGD::Point pos;
	SGD::Size screenSize;
	IEntity* target;
	float speed = 300;
	//bool locked;

	CCamera(IEntity* t, SGD::Size screen);
	~CCamera();
	void clamp();
public:

	static CCamera* GetInstance();
	bool Initiallize(IEntity* t, SGD::Size screen);
	bool Terminate();
	void DeleteInstance();

	void Update(float dt);
	SGD::Rectangle GetBoxInWorld() { return SGD::Rectangle(pos, screenSize); }
	float GetSpeed() {return speed;}
	void SetSpeed(float s) {speed = s;}
	void SetTarget(IEntity* t);
	SGD::Vector GetOffset() {return SGD::Point{0,0} - pos;}
	void SetScreenSize(SGD::Size newsize) {screenSize = newsize;}
};
