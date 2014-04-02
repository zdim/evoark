
#include "Particle.h"


CParticle::CParticle()
{
}


CParticle::CParticle(SGD::Color cColor, SGD::Point cPosition,
	float cLife, SGD::Vector cSpeed,
	SGD::Size cScale, float cRotation)
{
	curColor = cColor;
	curPosition = cPosition;
	curSpeed = cSpeed;
	curScale = cScale;
	m_fCurLife = cLife;
	m_fRotation = cRotation;
}

CParticle::~CParticle()
{

}

