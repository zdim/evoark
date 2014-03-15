
#include "Emitter.h"
#include "../../SGD Wrappers/SGD_Declarations.h"


CEmitter::CEmitter()
{}


CEmitter::CEmitter(CFlyweight parData, SGD::Size eSize, SGD::Point ePosition, int nParticles)
{
	particleData = parData;
	emitterSize = eSize;
	emitterPosition = ePosition;
	numParticles = nParticles;
}

CEmitter::~CEmitter()
{
}

void CEmitter::Update(float deltaTime)
{
	if (m_vParticles.size() < numParticles)
		CreateParticle();

	for (std::vector<CParticle>::iterator it = m_vParticles.begin(); it != m_vParticles.end(); ++it)
	{
		it->SetCurLife(it->GetCurLife() - deltaTime);

		if (it->GetCurLife() < 0)
			it->SetCurLife(0);

		// primitive movement 
		SGD::Point pos = {particleData.GetMaxVelX(), particleData.GetMaxVelY()};
//		pos.x += particleData.GetMaxVelX();
//		pos.y += particleData.GetMaxVelY();
		it->SetCurPos(pos);


		float fLifeCycle = it->GetCurLife() / particleData.GetMaxLife();

#pragma region Calc Particle Color Change


		float A = particleData.GetEndA() + fLifeCycle * (particleData.GetStartA() - particleData.GetEndA());
		float R = particleData.GetEndR() + fLifeCycle * (particleData.GetStartR() - particleData.GetEndR());
		float G = particleData.GetEndG() + fLifeCycle * (particleData.GetStartG() - particleData.GetEndG());
		float B = particleData.GetEndB() + fLifeCycle * (particleData.GetStartB() - particleData.GetEndB());

		if (A < 0) { A = 0; }
		else if (A > 255) { A = 255; }
		if (R > 255) { R = 255; }
		else if (R < 0) { R = 0; }
		if (G > 255) { G = 255; }
		else if (G < 0) { G = 0; }
		if (B > 255) { B = 255; }
		else if (B < 0) { B = 0; }

		SGD::Color curColor(A, R, G, B);

		it->SetCurColor(curColor);
#pragma endregion 

		// Calc Partical Scale Change 
		it->SetCurScale(particleData.GetEndScale() * fLifeCycle * (particleData.GetStartScale() - particleData.GetEndScale()));


		//Kill dead particles
		if (it->GetCurLife() <= 0)
			m_vParticles.erase(it);


	}
}




void CEmitter::Render()
{
	for (std::vector<CParticle>::iterator it = m_vParticles.begin(); it != m_vParticles.end(); ++it)
	{

	}
}

void CEmitter::CreateParticle()
{

	SGD::Color tempColor(particleData.GetStartA(), particleData.GetStartR(), particleData.GetStartG(), particleData.GetStartB());
	float      tempLife = particleData.GetMaxLife();
	float      tempVelX = particleData.GetMaxVelX();
	float      tempVelY = particleData.GetMaxVelY();
	float      tempScale = particleData.GetStartScale();
	CParticle tempParticle(tempColor, emitterPosition, tempLife, tempVelX, tempVelY, tempScale);
	m_vParticles.push_back(tempParticle);

}