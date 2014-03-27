//
#include "Missile.h"
#include "../../Graphics/Particles/ParticleSystem.h"

CMissile::CMissile()
{
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

//void CMissile::HandleCollision(IEntity* other)
//{
//	EntityType otherType = (EntityType)other->GetType();
//
//	//Is other a ship?
//	if (otherType >= EntityType::Player && otherType <= EntityType::Mamba)
//	{
//		CShip* ship = dynamic_cast<CShip*>(other);
//		ship->TakeDamage(damage);
//
//	}
//}

void CMissile::Update(float dt)
{
	CParticleSystem::GetInstance()->GetParticleEffect(2)->SetEmitterPosition(position);
	CParticleSystem::GetInstance()->GetParticleEffect(2)->Update(dt);
	CEntity::Update(dt);
}

void  CMissile::Render()
{
	CParticleSystem::GetInstance()->GetParticleEffect(2)->Render();
	CEntity::Render();

}