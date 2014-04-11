#pragma once

#include "Flyweight.h"
#include "../../SGD Wrappers/SGD_Color.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class CParticle
{
private:

	SGD::Color     curColor;
	SGD::Point     curPosition;
	SGD::Vector    curSpeed;
	SGD::Size      curScale;
	float          m_fCurLife;
	float          m_fRotation;
	

public:

	CParticle();

	CParticle(SGD::Color cColor, SGD::Point cPosition, 
		float cLife,SGD::Vector cSpeed,
		SGD::Size cScale, float cRotation );

	virtual ~CParticle();


	SGD::Color  GetCurColor()          { return curColor; }
	SGD::Point  GetCurPos()            { return curPosition; }
	SGD::Vector GetCurSpeed()          { return curSpeed; }
	SGD::Size   GetCurScale()          { return curScale; }
	float       GetCurLife()           { return m_fCurLife; }
	float       GetCurRotation()       { return m_fRotation; }


	void SetCurColor(SGD::Color c)     { curColor = c; }
	void SetCurPos(SGD::Point p)       { curPosition = p; }
	void SetCurSpeedX(float x)         { curSpeed.x = x; }
	void SetCurSpeedY(float y)         { curSpeed.y = y; }
	void SetCurSpeed(SGD::Vector s)    { curSpeed = s; }
	void SetCurScale(SGD::Size scale)  { curScale = scale; }
	void SetCurLife(float sLife)       { m_fCurLife = sLife; }
	void SetCurRotation(float rotation) { m_fRotation = rotation; }
	void Delete();
	
};

