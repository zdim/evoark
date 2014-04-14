#pragma once
#include <map>
#include <vector>
#include "../../SGD Wrappers/SGD_Handle.h"
#include "Emitter.h"
#include "Flyweight.h"

class CParticleSystem
{
	std::map<int,CEmitter*>                  particleEffect;
	int                                      numEmitters;
	std::list<CEmitter*>                     emittingPool;
	std::list<CEmitter*>                     standbyPool;

	CParticleSystem(CParticleSystem const&);           
	void operator=(CParticleSystem const&); 

	

public:
	CParticleSystem();
	~CParticleSystem();

	static	CParticleSystem*	GetInstance();
	static	void			    DeleteInstance();

	static CParticleSystem* s_Instance;

	  

	void Init();
	void Terminate();
	void Update(float dt);
	void Render();
	void LoadEffect(std::string effectName);
	void AddEmitter(int n,CEntity* owner);
	void AddEmitterPos(int n, SGD::Point pos);
	void RemoveEmitter(CEntity* owner);
	CEmitter* GetParticleEffect(int n ) { return particleEffect[n]; }

};


