
#include "Particle.h"


CParticle::CParticle()
{
}


CParticle::CParticle(SGD::Color cColor, SGD::Point cPosition,
	float CurLife,
	float CurVelX, float CurVelY,
	SGD::Size CurScale
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

RECT CParticle::GetRect(void) const
{
	RECT rSelf =
	{
		(LONG)curPosition.x,
		(LONG)curPosition.y,
		(LONG)(curPosition.x + 256),
		(LONG)(curPosition.y + 256)
	};

	return rSelf;
}
