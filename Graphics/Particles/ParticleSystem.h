#pragma once
#include <map>
#include "../../SGD Wrappers/SGD_Handle.h"
#include "Emitter.h"
#include "Flyweight.h"

class CParticleSystem
{
	std::map<int,CEmitter*>                  particleEffect;
	int                                      numEmitters;





public:
	CParticleSystem();
	~CParticleSystem();


	void Init();
	void Update(float dt);
	void Render();
	void LoadEffect(std::string effectName);

};

