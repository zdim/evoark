
#include "Flyweight.h"



CFlyweight::CFlyweight()
{}


CFlyweight::CFlyweight(
	  SGD::HTexture img, 
	  SGD::Size StartScale, SGD::Size EndScale,
	  unsigned char sA,
	  unsigned char sR,
	  unsigned char sG,
	  unsigned char sB,
	  unsigned char eA,
	  unsigned char eR,
	  unsigned char eG,
	  unsigned char eB,
	  float MaxLife, float MinLife, 
	  float VelXMax, float VelXMin, 
	  float VelYMax,float VelYMin) 
{

	image = img;


	m_fStartScale = StartScale;
	m_fEndScale = EndScale;

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

	m_fVelXMax = VelXMax;
	m_fVelXMin = VelXMin;

	m_fVelYMax = VelYMax;
	m_fVelYMin = VelYMin;

}


CFlyweight::~CFlyweight()
{
}
