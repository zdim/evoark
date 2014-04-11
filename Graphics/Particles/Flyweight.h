#pragma once
#include "../../SGD Wrappers/SGD_Color.h"
#include "../../SGD Wrappers/SGD_Handle.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class CFlyweight
{

private:
	SGD::HTexture image;

	
	SGD::Size         m_fStartScale;
	SGD::Size         m_fEndScale;
	SGD::Vector       rotationOffset;

	SGD::Vector       MinSpeed;
	SGD::Vector       MaxSpeed; 

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

	

	float m_fInertia;

	float m_fRotationSpeed;



public:

	CFlyweight::CFlyweight();

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
		SGD::Vector maxs,
		SGD::Vector mins,
		float Inertia,
		float RotationSpeed);

	~CFlyweight();

	void Release();

	//A&M
	SGD::HTexture GetImage() { return image; }

	SGD::Size GetStartScale() { return m_fStartScale; }
	SGD::Size GetEndScale()   { return m_fEndScale; }

	float GetMaxLife() { return m_fMaxLife; }
	float GetMinLife() { return m_fMinLife; }

	SGD::Vector GetMinSpeed() { return MinSpeed; }
	SGD::Vector GetMaxSpeed()   { return MaxSpeed; }
	SGD::Vector GetRotationOffset() { return rotationOffset; }
	float       GetInertia() { return m_fInertia; }
	float       GetRotaionSpeed() { return m_fRotationSpeed; }


	unsigned char GetStartA()   { return startA; }
	unsigned char GetStartR()   { return startR; }
	unsigned char GetStartG()   { return startG; }
	unsigned char GetStartB()   { return startB; }

	unsigned char GetEndA()     { return endA; }
	unsigned char GetEndR()     { return endR; }
	unsigned char GetEndG()     { return endG; }
	unsigned char GetEndB()     { return endB; }

	void Terminate(); 



};

