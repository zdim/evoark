//
#include "Missile.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../Graphics/Particles/Emitter.h"

CMissile::CMissile()
{
	m_pSystem = CParticleSystem::GetInstance();
	
	m_eTrail = new CEmitter(
		m_pSystem->GetParticleEffect(2)->GetParticleData(),
		m_pSystem->GetParticleEffect(2)->GetEmitterSize(),
		m_pSystem->GetParticleEffect(2)->GetShape(),
		position,
		m_pSystem->GetParticleEffect(2)->GetNumParticles(),
		m_pSystem->GetParticleEffect(2)->GetSpawnRate(),
		m_pSystem->GetParticleEffect(2)->GetSpawnTimeFromLastSpawn(),
		m_pSystem->GetParticleEffect(2)->GetEmitType(),
		m_pSystem->GetParticleEffect(2)->GetEmitTime()
		);
	m_eTrail->Initialize();
}


CMissile::~CMissile()
{
}

void CMissile::SetTarget(CShip* t)
{
	if (target)
		target->Release();

	target = t;

	if (target)
		target->AddRef();
}

void CMissile::HandleCollision(IEntity* other)
{
	EntityType otherType = (EntityType)other->GetType();

	//Is other a ship?
	if (otherType >= EntityType::Player && otherType <= EntityType::Mamba)
	{
		CShip* ship = dynamic_cast<CShip*>(other);
		ship->TakeDamage(damage);
		SelfDestruct();
	}
}

void CMissile::Update(float dt)
{
	m_eTrail->SetEmitterPosition(position);
    m_eTrail->Update(dt);
	CEntity::Update(dt);
}

void  CMissile::Render()
{
	m_eTrail->Render();
	CEntity::Render();

}