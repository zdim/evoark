#include "stdafx.h"
#include "Particle.h"


CParticle::CParticle()
{
}


CParticle::CParticle(SGD::Color cColor, SGD::Point cPosition,
	float CurLife,
	float CurVelX, float CurVelY,
	float CurScale
	)
{
	curColor = cColor;
	curPosition = cPosition;
	m_fCurLife = CurLife;
	m_fCurVelX = CurVelX;
	m_fCurVelY = CurVelY;
	m_fCurScale = CurScale;
}

CParticle::~CParticle()
{
}

