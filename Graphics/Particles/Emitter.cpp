
#include "Emitter.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

CEmitter::CEmitter()
{}


CEmitter::CEmitter(CFlyweight *parData, SGD::Size eSize, SGD::Point ePosition, int nParticles, float fSpawnRate, float fTimeFromLastSpawn, bool emway, float emitTime)
{
	particleData = parData;
	emitterSize = eSize;
	emitterPosition = ePosition;
	m_nNumParticles = nParticles;
	m_fSpawnRate = fSpawnRate;
	m_fTimeFromLastSpawn = 0;
	m_bEmitWay = emway;
	m_fEmitTime = emitTime;
}

CEmitter::~CEmitter()
{
}

void CEmitter::Initialize()
{
	for (int i = 0; i < m_nNumParticles; i++)
	{
		CParticle * emptyParticle = new CParticle();
		m_lDeadParticles.push_back(emptyParticle);
	}
	
}

void CEmitter::Update(float deltaTime)
{
	m_fTimeFromLastSpawn += deltaTime;
	m_fEmitTime -= deltaTime;
	
	
		

	while (m_fTimeFromLastSpawn >= m_fSpawnRate)
	{
		if (m_fEmitTime <= 0 && m_bEmitWay == false)
			break;
		m_fTimeFromLastSpawn -= m_fSpawnRate;
		CParticle * p = *m_lDeadParticles.begin();
		*p = CreateParticle();
		m_lDeadParticles.pop_front();
		m_lAliveParticles.push_front(p);
	}
	

	for (std::list<CParticle*>::iterator it = m_lAliveParticles.begin() ; it != m_lAliveParticles.end(); )
		{
		

		(*it)->SetCurLife((*it)->GetCurLife() - deltaTime);

		if ((*it)->GetCurLife() < 0)
			(*it)->SetCurLife(0);

			// primitive movement 
		   
			SGD::Point pos = (*it)->GetCurPos() + SGD::Vector { particleData->GetMaxVelX() * deltaTime, particleData->GetMaxVelY() * deltaTime };
			(*it)->SetCurPos(pos);




			float fLifeCycle = (*it)->GetCurLife() / particleData->GetMaxLife();

#pragma region Calc Particle Color Change


			float A = particleData->GetEndA() + fLifeCycle * (particleData->GetStartA() - particleData->GetEndA());
			float R = particleData->GetEndR() + fLifeCycle * (particleData->GetStartR() - particleData->GetEndR());
			float G = particleData->GetEndG() + fLifeCycle * (particleData->GetStartG() - particleData->GetEndG());
			float B = particleData->GetEndB() + fLifeCycle * (particleData->GetStartB() - particleData->GetEndB());

			if (A < 0) { A = 0; }
			else if (A > 255) { A = 255; }
			if (R > 255) { R = 255; }
			else if (R < 0) { R = 0; }
			if (G > 255) { G = 255; }
			else if (G < 0) { G = 0; }
			if (B > 255) { B = 255; }
			else if (B < 0) { B = 0; }

			SGD::Color curColor(A, R, G, B);

			(*it)->SetCurColor(curColor);
#pragma endregion 

			// Calc Partical Scale Change 
			(*it)->SetCurScale(particleData->GetEndScale() * fLifeCycle * (particleData->GetStartScale() - particleData->GetEndScale()));


			//Kill dead particles
			if ((*it)->GetCurLife() <= 0)
			{
				m_lDeadParticles.push_back(*it);
				it = m_lAliveParticles.erase(it);
				continue;
			}
				
			it++;

		}
}





void CEmitter::Render()
{
	for (std::list<CParticle*>::iterator it = m_lAliveParticles.begin(); it != m_lAliveParticles.end(); ++it)
	{
		SGD::Vector test{ 0, 0 };
		SGD::Size testscale { 0.05f, 0.05f };
		
		SGD::GraphicsManager::GetInstance()->DrawTexture(particleData->GetImage(), (*it)->GetCurPos(), 0.0f, test, (*it)->GetCurColor(), testscale);
	}
}

CParticle CEmitter::CreateParticle()
{

	SGD::Color tempColor(particleData->GetStartA(), particleData->GetStartR(), particleData->GetStartG(), particleData->GetStartB());
	float      tempLife = particleData->GetMaxLife();
	float      tempVelX = particleData->GetMaxVelX();
	float      tempVelY = particleData->GetMaxVelY();
	float      tempScale = particleData->GetStartScale();
	CParticle tempParticle(tempColor, emitterPosition, tempLife, tempVelX, tempVelY, tempScale);
	return tempParticle;
}