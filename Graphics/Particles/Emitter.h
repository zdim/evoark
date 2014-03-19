#pragma once
#include <list>
#include "Particle.h"
#include "Flyweight.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class CEmitter
{

private:
	std::list<CParticle*>   m_lAliveParticles;
	std::list<CParticle*>   m_lDeadParticles;
	CFlyweight             *particleData;
	SGD::Size              emitterSize;
	SGD::Point             emitterPosition;
	int                    m_nNumParticles;
	float                  m_fSpawnRate;
	float                  m_fTimeFromLastSpawn;
	bool                   m_bLoop;
	float                  m_fEmitTime;
	int                    shape; 
	




public:
	CEmitter(); 
	CEmitter(CFlyweight *parData, SGD::Size eSize, SGD::Point ePosition, int nParticles, float fSpawnRate,
	float fTimeFromLastSpawn, bool emway, float emitTime = 0 );
	virtual ~CEmitter();
	void Initialize();
	void Update(float deltaTime);
	void Render();
	CParticle CreateParticle();



	SGD::Point GetEmitterPosition() { return emitterPosition; }
	



};

