
#include "Flyweight.h"



CFlyweight::CFlyweight()
{}


CFlyweight::CFlyweight(
	  SGD::HTexture img, 
	  SGD::Size StartScale, SGD::Size EndScale,
	  SGD::Vector       rOffset,
	  unsigned char sA,
	  unsigned char sR,
	  unsigned char sG,
	  unsigned char sB,
	  unsigned char eA,
	  unsigned char eR,
	  unsigned char eG,
	  unsigned char eB,
	  float MaxLife, float MinLife, 
	  SGD::Vector s,
	  float  Inertia,
	  float RotationSpeed)
{

	image = img;


	m_fStartScale = StartScale;
	m_fEndScale = EndScale;

	rotationOffset = rOffset;

	startA = sA;
	startR = sR;
	startG = sG;
	startB = sB;
	       
	endA = eA;
	endR = eR;
	endG = eG;
	endB = eB;
	
	m_fMaxLife = MaxLife;
	m_fMinLife = MinLife;

	speed = s;
	m_fInertia = Inertia;
	m_fRotationSpeed = RotationSpeed;

}


CFlyweight::~CFlyweight()
{
}
