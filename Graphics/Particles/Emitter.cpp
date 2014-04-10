
#include "Emitter.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../Camera.h"
//#include <stdlib.h>

CEmitter::CEmitter()
{}


CEmitter::CEmitter(CFlyweight *parData, SGD::Size eSize, int s, SGD::Point ePosition, int nParticles, float fSpawnRate, float fTimeFromLastSpawn, bool emway, float emitTime)
{
	particleData = parData;
	shape = s;
	emitterSize = eSize;
	emitterPosition = ePosition;
	m_nNumParticles = nParticles;
	m_fSpawnRate = fSpawnRate;
	m_fTimeFromLastSpawn = 0;
	m_bLoop = emway;
	m_fEmitTime = emitTime;
}

CEmitter::~CEmitter()
{
	m_lAliveParticles.clear();
	m_lDeadParticles.clear();
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

	if (m_fTimeFromLastSpawn >= m_fSpawnRate)
	{
		if (m_fEmitTime >= 0 && m_bLoop == false && m_lDeadParticles.size() != 0)
		{
			m_fTimeFromLastSpawn -= m_fSpawnRate;
			CParticle * p = *m_lDeadParticles.begin();
			*p = CreateParticle();
			m_lDeadParticles.pop_front();
			m_lAliveParticles.push_front(p);
		}
		else if (m_bLoop == true && m_lDeadParticles.size() != 0)
		{
			m_fTimeFromLastSpawn -= m_fSpawnRate;
			CParticle * p = *m_lDeadParticles.begin();
			*p = CreateParticle();
			m_lDeadParticles.pop_front();
			m_lAliveParticles.push_front(p);

		}

	}


	for (std::list<CParticle*>::iterator it = m_lAliveParticles.begin(); it != m_lAliveParticles.end();)
	{
		(*it)->SetCurLife((*it)->GetCurLife() - deltaTime);
		if ((*it)->GetCurLife() < 0)
			(*it)->SetCurLife(0);



#pragma region Inertia

		if ((*it)->GetCurSpeed().x > 0 && (*it)->GetCurSpeed().y > 0)
		{
			SGD::Vector temp{ (*it)->GetCurSpeed().x - (particleData->GetInertia() * deltaTime), (*it)->GetCurSpeed().y - (particleData->GetInertia() * deltaTime) };
			(*it)->SetCurSpeed(temp);
			if ((*it)->GetCurSpeed().x < 0 && (*it)->GetCurSpeed().y < 0)
			{
				SGD::Vector temp{ 0, 0 };
				(*it)->SetCurSpeed(temp);
			}

		}
		else if ((*it)->GetCurSpeed().x < 0 && (*it)->GetCurSpeed().y < 0)
		{
			SGD::Vector temp{ (*it)->GetCurSpeed().x + (particleData->GetInertia() * deltaTime), (*it)->GetCurSpeed().y + (particleData->GetInertia() * deltaTime) };
			(*it)->SetCurSpeed(temp);
			if ((*it)->GetCurSpeed().x > 0 && (*it)->GetCurSpeed().y > 0)
			{
				SGD::Vector temp{ 0, 0 };
				(*it)->SetCurSpeed(temp);
			}

		}
		(*it)->SetCurPos((*it)->GetCurPos() + ((*it)->GetCurSpeed() * deltaTime));
#pragma endregion

		(*it)->SetCurRotation((*it)->GetCurRotation() + (particleData->GetRotaionSpeed() / 2 * deltaTime));


		// Calculating the life of One particle 
		float fLifeCycle = (*it)->GetCurLife() / particleData->GetMaxLife();

#pragma region Particle Color Change


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

		SGD::Color curColor((int)A, (int)R, (int)G, (int)B);

		(*it)->SetCurColor(curColor);
#pragma endregion 
	
		SGD::Size curSize { particleData->GetEndScale().width + fLifeCycle * (particleData->GetStartScale().width - particleData->GetEndScale().width),
			particleData->GetEndScale().height + fLifeCycle * (particleData->GetStartScale().height - particleData->GetEndScale().height) };
		

		if (particleData->GetStartScale() != particleData->GetEndScale())
			(*it)->SetCurScale(curSize);


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
		SGD::Point tPoint = { (*it)->GetCurPos().x - (particleData->GetRotationOffset().x * (*it)->GetCurScale().width),
			(*it)->GetCurPos().y - particleData->GetRotationOffset().y * (*it)->GetCurScale().height };

		tPoint += CCamera::GetInstance()->GetOffset();

		SGD::GraphicsManager::GetInstance()->DrawTexture(particleData->GetImage(), tPoint, (*it)->GetCurRotation(),
			particleData->GetRotationOffset(), (*it)->GetCurColor(), (*it)->GetCurScale());
	}
}


CParticle CEmitter::CreateParticle()
{


	SGD::Color tempColor{ particleData->GetStartA(), particleData->GetStartR(), particleData->GetStartG(), particleData->GetStartB() };

	float randLife = particleData->GetMinLife() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (particleData->GetMaxLife() - particleData->GetMinLife())));

	SGD::Vector randSpeed = { particleData->GetMinSpeed().x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (particleData->GetMaxSpeed().x - particleData->GetMinSpeed().x))),
		particleData->GetMinSpeed().y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (particleData->GetMaxSpeed().y - particleData->GetMinSpeed().y))) };

	SGD::Point ppositionn{ emitterPosition.x + (rand() % (int)emitterSize.width),
		emitterPosition.y + (rand() % (int)emitterSize.height) };

	SGD::Size tScale{ particleData->GetStartScale().width, particleData->GetStartScale().height };


	if (shape == 4)
	{

		float radius = emitterSize.width / 2;

		SGD::Point EmitterCenter{ emitterPosition.x + emitterSize.width / 2
			, emitterPosition.y + emitterSize.height / 2 };

		float distance = sqrt((float)(EmitterCenter.x - ppositionn.x)*(EmitterCenter.x - ppositionn.x) +
			(EmitterCenter.y - ppositionn.y)*(EmitterCenter.y - ppositionn.y));

		do
		{
			ppositionn = { emitterPosition.x + (rand() % (int)emitterSize.width),
				emitterPosition.y + (rand() % (int)emitterSize.width) };
			distance = sqrt((float)(EmitterCenter.x - ppositionn.x)*(EmitterCenter.x - ppositionn.x) +
				(EmitterCenter.y - ppositionn.y)*(EmitterCenter.y - ppositionn.y));

		} while (distance >= radius);

	}

	return CParticle (tempColor, ppositionn, randLife, particleData->GetMinSpeed(), tScale, 0);

}


void CEmitter::Release()
{
	if (m_lAliveParticles.size() > 0)
	{
		for (std::list<CParticle*>::iterator it = m_lAliveParticles.begin(); it != m_lAliveParticles.end();)
		{
			delete *it;
			it++;
		}
			
	}

	if (m_lDeadParticles.size() > 0)
	{
		for (std::list<CParticle*>::iterator it = m_lDeadParticles.begin(); it != m_lDeadParticles.end();)
		{
			delete *it;
			it++;
		}
	}
	


	m_lAliveParticles.clear();
	m_lDeadParticles.clear();

	//particleData->Terminate();
	//delete particleData;
}