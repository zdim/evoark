//
#include "Mamba.h"
#include "../../EntityManager.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../../Graphics/Particles/ParticleSystem.h"

CMamba::CMamba()
{
	damage = 35;
	maxHull = 400;
	hull = maxHull;
	size = { 52, 80 };
	imageSize = { 64, 128 };


	m_Engine = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(29)->GetEmitTime()
		);


	m_Engine->Initialize();
	m_Engine->SetOwner(this);

	m_Engine2 = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitTime()
		);


	m_Engine2->Initialize();
	m_Engine2->SetOwner(this);


	m_Engine3 = new CEmitter(
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetParticleData(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitterSize(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetShape(),
		position,
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetNumParticles(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetSpawnRate(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetSpawnTimeFromLastSpawn(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitType(),
		CParticleSystem::GetInstance()->GetParticleEffect(19)->GetEmitTime()
		);


	m_Engine3->Initialize();
	m_Engine3->SetOwner(this);
}


CMamba::~CMamba()
{
	m_Engine->Release();
	delete m_Engine;
	m_Engine2->Release();
	delete m_Engine2;
	m_Engine3->Release();
	delete m_Engine3;
}



void CMamba::Render()
{
	m_Engine->Render();
	m_Engine2->Render();
	m_Engine3->Render();

	SGD::Rectangle rShipRegion = SGD::Rectangle(SGD::Point{ 0, 0 }, size);

	SGD::Point renderPoint = offsetToCamera();
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}

	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint, rShipRegion, rotation, size / 2, col);
}


void CMamba::Update(float dt)
{


	SGD::Vector rotatedOffset = { 0, 35 };
	rotatedOffset.Rotate(rotation);
	enginePos = position + rotatedOffset;

	m_Engine->SetEmitterPosition(enginePos);
	m_Engine->Update(dt);


	SGD::Vector rotatedOffset2 = { 15, 35 };
	rotatedOffset2.Rotate(rotation);
	enginePos2 = position + rotatedOffset2;

	m_Engine2->SetEmitterPosition(enginePos2);
	m_Engine2->Update(dt);

	SGD::Vector rotatedOffset3 = { -15, 35 };
	rotatedOffset3.Rotate(rotation);
	enginePos3 = position + rotatedOffset3;

	m_Engine3->SetEmitterPosition(enginePos3);
	m_Engine3->Update(dt);




	if (CEntityManager::GetInstance()->GetPlayer() && CEntityManager::GetInstance()->GetPlayer()->GetTutorialPause() != -1)
		return;

	SGD::Vector dir = CCopperhead::AI(dt);

	CEnemy::Update(dt);
	CEntity::Update(dt);


}



