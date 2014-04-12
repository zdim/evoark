//
#include "Enemy.h"
#include "../../EntityManager.h"
#include "../../Leader.h"
#include "../../../Event System/EventID.h"
#include "../../../Event System/CustomEvent.h"
#include "../../../Event System/EventManager.h"
#include "../../../GameStates/Game.h"
#include "../../../Message System/CreateProjectile.h"
#include "../../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../../SoundBox.h"
#include "../../Projectiles/Laser.h"
#include "../../Collidables/Asteroid.h"

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Update(float dt)
{
	if (CEntityManager::GetInstance()->GetPlayer()->GetTutorialPause() != -1)
		return;

	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;

	if (target)
	{
		SGD::Vector tarDir = target->GetPosition() - position;
		tarDir.Normalize();
		rotateToward(tarDir, dt);
	}
	else
	{
		SGD::Vector forward = {0,-1};
		forward.Rotate(rotation);
		forward.Rotate(SGD::PI/2.1f);
		rotateToward(forward, dt);
	}

	//Comment out later:
	//if (target)
	//{
	//	SGD::Vector dir = target->GetPosition() - position;
	//	if (dir.ComputeLength() > 100)
	//	{
	//		dir.Normalize();
	//		velocity = dir * speed;
	//	}
	//	else velocity = {0,0};
	//}
	//else
	//{
	//	velocity = { 0, 0 };
	//}

	if (avoid)
	{
		if (CalculateCollisionTime(avoid) == -1)
			SetAvoid(nullptr);
	}

	SGD::Vector forward = { 0, -1 };
	forward.Rotate(rotation);
	SGD::Vector dir;
	if(avoid)
	{
		dir = avoid->GetVelocity();
		dir.Normalize();
		float clockwise = dir.ComputeSteering(forward);
		if (clockwise > 0)
			dir.Rotate(SGD::PI * -0.5f);
		else
			dir.Rotate(SGD::PI * 0.5f);
		velocity = dir * speed;
		float strafeAngle = forward.ComputeAngle(dir);
		strafeAngle /= SGD::PI;
		strafeAngle = 1 - strafeAngle;
		velocity *= strafeAngle;
	}
	else if (position != destination)
	{
		dir = destination - position;
		float distance = dir.ComputeLength();
		dir.Normalize();
		if (distance >= speed || avoid)
		{
			velocity = dir * speed;
		}
		else
			velocity = dir * distance;
		float strafeAngle = forward.ComputeAngle(dir);
		strafeAngle /= SGD::PI;
		strafeAngle = 1 - strafeAngle;
		velocity *= strafeAngle;
	}
	else
	{
		velocity = {0,0};
	}

	//Add evasive direction to velocity

	//Update position based on velocity
	//CEntity::Update(dt);

	CCustomEvent* e = new CCustomEvent(EventID::position, nullptr, this);
	e->Queue();
}

void CEnemy::Render()
{
	SGD::Size scale = SGD::Size{ size.width / imageSize.width, size.height / imageSize.height };
	//CCamera* cam = Game::GetInstance()->GetLevelState()->GetCam();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
	SGD::Point renderPoint = offsetToCamera();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, renderPoint,SGD::Rectangle{SGD::Point{0,0}, imageSize}, rotation, imageSize/2, {}, scale);
	SGD::Color col = {};
	if (damaged > 0)
	{
		col = { 155, 155, 155 };
	}
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, col, scale);
}

void CEnemy::SetTarget(CShip* newTarget)
{
	if (target == newTarget)
		return;

	if ((unsigned int)target == 0xfeeefeee)
	{
		target = nullptr;
	}
	if (newTarget && newTarget->GetType() == (int)EntityType::Human)
	{
		target = nullptr;
	}

	if (target)
		target->Release();

	target = newTarget;

	if (target)
		target->AddRef();
}

void CEnemy::HandleEvent(CCustomEvent* e)
{
	EventID id = e->GetID();
	switch (id)
	{
	case EventID::position:
	{
		IEntity* other = dynamic_cast<IEntity*> (e->GetSender());
		if (other == this)
			return;
		if (other->IsDestroying())
			return;
		EntityType otherType = (EntityType)other->GetType();
		if (otherType == EntityType::Human || otherType == EntityType::Player)
		{
			DetectShip(dynamic_cast<CShip*>(other));
		}
		//detect projectiles and collidables

		//Calculate how long it will take to collide
		float collisionTime = CalculateCollisionTime(other);
		//-1 means it won't collide
		if (collisionTime == -1)
			break;


		//Between the width and height of the potential new avoid
		float larger = std::max(size.width * 2, std::max(size.height * 2, std::max(other->GetSize().width, other->GetSize().height)));
		//Calculate the amount of time it should take to dodge the object at the avoid pointer.
		float dodgeTime = larger/speed;
		//If there is no current avoid
		if (!avoid)
		{
			//If it will collide soon enouggh for us to worry about taking damage
			if(collisionTime < dodgeTime * 2 && CalculateDamage(other) > 0)
				//Avoid other
				SetAvoid(other);
			//We're done
			break;
		}

		//We have another avoid, recalculate dodgetime based on it's size too
		//Get the new largest dimension, including the old thing's size
		larger = std::max(larger, std::max(avoid->GetSize().width, avoid->GetSize().height));
		//recalculat dodgetime
		dodgeTime = larger/speed;

		//Calculate the collision time for the old collider
		float oldCollisionTime = CalculateCollisionTime(avoid);
		//calculate the differnce between the collision times
		float timeDiff = abs(oldCollisionTime - collisionTime);

		//If we can't dodge both
		if (timeDiff < dodgeTime)
		{
			//Get the damage of each
			float dam = CalculateDamage(other);
			if (dam <= 0)
				return;
			float oldDam = CalculateDamage(avoid);
			//If the new thing does more damage than the old thing
			if (dam > oldDam)
				//Avoid the new thing
				SetAvoid(other);
			//We're done
			return;
		}
		
		//If the new thing will collide earlier than the old thing
		if (collisionTime < oldCollisionTime && CalculateDamage(other) >= 0)
		{
			//Avoid the new thing
			SetAvoid(other);
		}
	}
	}
}

void CEnemy::DetectShip(CShip* other)
{
		SGD::Point pos = other->GetPosition();
		SGD::Vector toTarget = pos - position;

		SGD::Vector forward = { 0, -1 };
		forward.Rotate(rotation);
		//"delta rotation" the amount of rotation it will take to face the target.
		float angle = forward.ComputeAngle(toTarget);
		if (angle >= SGD::PI / 4.0f)
			return;

	float distance = toTarget.ComputeLength();
	if (distance >= SGD::Vector{ (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() }.ComputeLength() * 0.5f)
	{
		//if (other == target)
		//	SetTarget(nullptr);
		return;
	}
		SetTarget(other);
		if (leader)
			leader->SetTarget(other);
}

void CEnemy::TakeDamage(int damage, bool collision)
{
	//if (shield > 0)
	//{
	//	shield -= damage;
	//	damage -= shield;
	//}
	//
	//if (damage <= 0)
	//{
	//	return;
	//}
	if (collision)
		damage *= COLLISION_MODIFIER;
	CSoundBox::GetInstance()->Play(CSoundBox::sounds::enemyShieldDamage, false);
	hull -= damage;
	damaged = .15f;
	if (hull <= 0)
	{

		SelfDestruct();
	}
}

void CEnemy::SelfDestruct()
{
	if (destroying)
		return;

	CShip::SelfDestruct();
	CEventManager::GetInstance().UnregisterAll(this);
}

void CEnemy::SetAvoid(IEntity* newAvoid)
{
  	if (avoid)
		avoid->Release();

	avoid = newAvoid;

	if (avoid)
		avoid->AddRef();
}

float CEnemy::CalculateCollisionTime(IEntity* other)
{
	SGD::Vector vel = other->GetVelocity();
	SGD::Vector toMe = position - other->GetPosition();

	float distance = toMe.ComputeLength(); //"meters"
	float otherspeed = vel.ComputeLength(); //"meters/second"
	float time = distance / otherspeed;	//"seconds = meters / 1 * seconds / meters
	//seconds / meters = recipricol of speed. distance * 1/speed = distance over speed.
	//Let's hope that works.

	SGD::Rectangle otherRect = other->GetRect();
	SGD::Rectangle myRect = GetRect();
	myRect.left -= size.width/2;
	myRect.right += size.width/2;
	myRect.top -= size.height/2;
	myRect.bottom += size.height/2;
	SGD::Size otherSize = other->GetSize();
	otherRect.MoveTo((other->GetPosition() + vel * time) - otherSize/2);

	if (!otherRect.IsIntersecting(myRect))
	{
		//See if we're heading toawrd them instead
		time = distance/speed;
		SGD::Rectangle otherRect = other->GetRect();
		SGD::Rectangle myRect = GetRect();
		otherRect.left -= otherSize.width / 2;
		otherRect.right += otherSize.width / 2;
		otherRect.top -= otherSize.height / 2;
		otherRect.bottom += otherSize.height / 2;
		myRect.MoveTo((position + velocity * time) - size/2);
		if (!otherRect.IsIntersecting(myRect))
			return -1;
	}
	return time;
}

int CEnemy::CalculateDamage(IEntity* other)
{
	EntityType type = (EntityType)other->GetType();
	//CEnemy fake;
	//fake.setHull(INT_MAX);
	if (type >= EntityType::Player && type <= EntityType::Coordinator)
	{
		EntityType myType = (EntityType)GetType();
		if (myType == EntityType::Moccasin || myType == EntityType::Coral)
			return 0;
		CShip* ship = dynamic_cast<CShip*>(other);
		SGD::Size shipsize = ship->GetSize();
		float mass = shipsize.width * shipsize.height / 100;
		return mass * ship->getSpeed() * COLLISION_MODIFIER;
	}

	if (type == EntityType::Laser || type == EntityType::Missile)
	{
		CLaser* proj = dynamic_cast<CLaser*>(other);
		IEntity* owner = proj->GetOwner();
		if (owner->GetType() == (int)EntityType::Player || owner->GetType() == (int)EntityType::Human)
		{
			return proj->GetDamage();
		}
		else return 0;
	}

	if (type == EntityType::Asteroid)
	{
		CAsteroid* ast = dynamic_cast<CAsteroid*>(other);
		SGD::Size astsize = ast->GetSize();
		float mass = astsize.width * astsize.height / 10;
		return mass * ast->GetSpeed() * COLLISION_MODIFIER;
	}

	return 0;
	//other->HandleCollision(&fake);
	//int otherDam = INT_MAX - fake.getHull();
	//CEventManager::GetInstance().UnregisterAll(&fake);
	//return otherDam;
}
