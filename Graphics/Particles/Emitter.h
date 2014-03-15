#pragma once
#include <vector>
#include "Particle.h"
#include "Flyweight.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class CEmitter
{

private:
	std::vector<CParticle> m_vParticles;
	CFlyweight             particleData;
	SGD::Size              emitterSize;
	SGD::Point             emitterPosition;
	int                    numParticles;
	




public:
	CEmitter(); 
	CEmitter(CFlyweight parData, SGD::Size eSize, SGD::Point ePosition,int nParticles);
	virtual ~CEmitter();
	void Update(float deltaTime);
	void Render();
	void CreateParticle();


	



};

