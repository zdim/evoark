//
#include "Missile.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../Graphics/Particles/Emitter.h"

CMissile::CMissile()
{
	
	m_eTrail = new CEmitter(CParticleSystem::GetInstance()->GetParticleData(1), { 1, 1 },1,position,20,0.1,0.2,true,0.0);
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