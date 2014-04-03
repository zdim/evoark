//
#include "Missile.h"
#include "../../Graphics/Particles/ParticleSystem.h"
#include "../../Graphics/Particles/Emitter.h"
#include "../../Event System/EventManager.h"
#include "../../Event System/EventID.h"
#include "../../Event System/CustomEvent.h"
#include "../../Camera.h"

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

	CEventManager::GetInstance().Register(dynamic_cast<Listener*>(this), EventID::position);
}


CMissile::~CMissile()
{
	
	delete target;
	delete m_eTrail;
}

void CMissile::SelfDestruct()
{
	CEntity::SelfDestruct();
	SetTarget(nullptr);
	CEventManager::GetInstance().Unregister(dynamic_cast<Listener*>(this), EventID::position);
}

void CMissile::SetTarget(CShip* t)
{
	if (target == t)
		return;

	if (target)
		target->Release();

	if (t)
		t->AddRef();

	target = t;

}



void CMissile::Update(float dt)
{

	CLaser::Update(dt);

	if (target != nullptr)
	{
	

		SGD::Vector vToTarget =
		{
			target->GetPosition().x - position.x,
			target->GetPosition().y - position.y ,
		};

		vToTarget.Normalize();

		rotateToward(vToTarget, dt);

		SGD::Vector direction = { 0, -1 };

		direction.Rotate(rotation);
		
		velocity = direction * 500;

	}

	m_eTrail->SetEmitterPosition(position);
    m_eTrail->Update(dt);


}

void  CMissile::Render()
{
	m_eTrail->Render();
	CEntity::Render();

}

void CMissile::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::position:
	{
							  IEntity* other = dynamic_cast<IEntity*> (e->GetSender());
							  EntityType otherType = (EntityType)other->GetType();

							  

							  if (otherType >= EntityType::Copperhead && otherType <= EntityType::Moccasin && CCamera::GetInstance()->GetBoxInWorld().IsIntersecting(other->GetRect()) == true && tier == 3 )
							  {
								  if (target == nullptr)
								  {
									  SetTarget(dynamic_cast<CShip*>(other));
									  return; 
								  }

								  SGD::Vector vToNewTarget = other->GetPosition() - position;					
								  SGD::Vector vToOldTarget = target->GetPosition() - position;

								  SGD::Vector direction = { 0, -1 };
								  direction.Rotate(rotation);

								  float m_fNewTarget = direction.ComputeAngle(vToNewTarget);
								  float m_fOldTarget = direction.ComputeAngle(vToOldTarget);

								  if (CCamera::GetInstance()->GetBoxInWorld().IsIntersecting(other->GetRect()) == true && m_fNewTarget < m_fOldTarget)
								  {
									  SetTarget(dynamic_cast<CShip*>(other));
								  }
							  }

							  break;
	}
	}
}