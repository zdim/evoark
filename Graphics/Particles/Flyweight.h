#pragma once
#include "../../SGD Wrappers/SGD_Color.h"
#include "../../SGD Wrappers/SGD_Handle.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class CFlyweight
{

private:
	SGD::HTexture image;

	
	SGD::Size m_fStartScale;
	SGD::Size m_fEndScale;

	unsigned char       startA;
	unsigned char       startR;
	unsigned char       startG;
	unsigned char       startB;

	unsigned char       endA;
	unsigned char       endR;
	unsigned char       endG;
	unsigned char       endB;


	float m_fMaxLife;
	float m_fMinLife;

	float m_fVelXMax;
	float m_fVelXMin;

	float m_fVelYMax;
	float m_fVelYMin;



public:

	CFlyweight::CFlyweight();

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
		float VelYMax, float VelYMin);

	~CFlyweight();


	//A&M
	SGD::HTexture GetImage() { return image; }

	SGD::Size GetStartScale() { return m_fStartScale; }
	SGD::Size GetEndScale()   { return m_fEndScale; }

	float GetMaxLife() { return m_fMaxLife; }
	float GetMinLife() { return m_fMinLife; }

	float GetMaxVelX() { return m_fVelXMax; }
	float GetMinVelX() { return m_fVelXMin; }

	float GetMaxVelY() { return m_fVelYMax; }
	float GetMinVelY() { return m_fVelYMin; }


	unsigned char GetStartA()   { return startA; }
	unsigned char GetStartR()   { return startR; }
	unsigned char GetStartG()   { return startG; }
	unsigned char GetStartB()   { return startB; }

	unsigned char GetEndA()     { return endA; }
	unsigned char GetEndR()     { return endR; }
	unsigned char GetEndG()     { return endG; }
	unsigned char GetEndB()     { return endB; }





};

