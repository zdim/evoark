#pragma once
#include <list>
#include "Particle.h"
#include "Flyweight.h"
#include "../../Entities/Ships/Ship.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class CEmitter
{

private:
	std::list<CParticle*>   m_lAliveParticles;
	std::list<CParticle*>   m_lDeadParticles;
	CFlyweight              *particleData;
	int                     shape;
	SGD::Size               emitterSize;
	SGD::Point              emitterPosition;
	int                     m_nNumParticles;
	float                   m_fSpawnRate;
	float                   m_fTimeFromLastSpawn;
	bool                    m_bLoop;
	float                   m_fEmitTime;
	float                   m_fSavedEmitTime;
	CEntity*                m_pShipOwner;




public:
	CEmitter(); 
	CEmitter(CFlyweight *parData, SGD::Size eSize,int s, SGD::Point ePosition, int nParticles, float fSpawnRate,
	float fTimeFromLastSpawn, bool emway, float emitTime = 0 );
	virtual ~CEmitter();
	void Initialize();
	void Update(float deltaTime);
	void Render();
	CParticle CreateParticle();
	void Release();
	void Reset();

	SGD::Point GetEmitterPosition() { return emitterPosition; }
	void       SetEmitterPosition(SGD::Point p) { emitterPosition = p; }
	SGD::Size  GetEmitterSize() { return emitterSize; }
	CFlyweight* GetParticleData() { return particleData; }
	int        GetNumParticles() { return m_nNumParticles; }
	int        GetShape() { return shape; }
	float      GetSpawnRate() { return m_fSpawnRate; }
	float      GetSpawnTimeFromLastSpawn() { return m_fTimeFromLastSpawn; }
	bool       GetEmitType() { return m_bLoop; }
	void       SetEmitType(bool b) { m_bLoop = b;  }
	float      GetEmitTime() { return m_fEmitTime; }
	void       SetOwner(CEntity* p)    { m_pShipOwner = p; }
	CEntity*   GetOwner() { return m_pShipOwner;  }
	int  GetLiveListSize() { return m_lAliveParticles.size(); }
};

