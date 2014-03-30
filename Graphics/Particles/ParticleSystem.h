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
	int numData;
	std::vector<CFlyweight*>                    Flyweights;

	CParticleSystem(CParticleSystem const&);           
	void operator=(CParticleSystem const&); 

	

public:
	CParticleSystem();
	~CParticleSystem();

	static	CParticleSystem*	GetInstance();
	static	void			    DeleteInstance();

	static CParticleSystem* s_Instance;

	  

	void Init();
	void Update(float dt);
	void Render();
	void LoadEffect(std::string effectName);
	void ResetEffect(int num);
	CEmitter* GetParticleEffect(int n ) { return particleEffect[n]; }
	CFlyweight* GetParticleData(int n)   { return Flyweights[n]; }

};


