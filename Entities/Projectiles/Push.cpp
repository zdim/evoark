//
#include "Push.h"
#include "../../GameStates/Game.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

CPush::CPush()
{
	radius = SGD::PI /4.0f;
	duration = 0.3;
	size = {512,512};
	imageSize = { 512, 512 };

	pushZero  = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/push0.png");
	pushOne   = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/push1.png");
	pushTwo   = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/push2.png");
	pushThree = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/push3.png");
}



CPush::~CPush()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(pushOne);
}

void CPush::Update(float dt)
{
	life += dt;
	
	if (life <= .10f)
	{
		alpha = life / .10f * 200;
	}

	else
		alpha = 200 - 200 * (life - .10f) / .20f;

	CEntity::Update(dt);

	if (life > duration)
		SelfDestruct();
}

void CPush::Render()
{
	switch (tier)
	{
	case 0:
		SGD::GraphicsManager::GetInstance()->DrawTexture(pushZero, offsetToCamera(), rotation, SGD::Size{ 512, 512 } *.5f, SGD::Color{ (unsigned char)alpha, (unsigned char)255, (unsigned char)255, (unsigned char)255 });
		break;
	case 1:
		SGD::GraphicsManager::GetInstance()->DrawTexture(pushOne, offsetToCamera(), rotation, SGD::Size{ 512, 512 } *.5f, SGD::Color{ (unsigned char)alpha, (unsigned char)255, (unsigned char)255, (unsigned char)255 });
		break;
	case 2:
		SGD::GraphicsManager::GetInstance()->DrawTexture(pushTwo, offsetToCamera(), rotation, SGD::Size{ 512, 512 } *.5f, SGD::Color{ (unsigned char)alpha, (unsigned char)255, (unsigned char)255, (unsigned char)255 });
		break;
	case 3:
		SGD::GraphicsManager::GetInstance()->DrawTexture(pushThree, offsetToCamera(), rotation, SGD::Size{ 512, 512 } *.5f, SGD::Color{ (unsigned char)alpha, (unsigned char)255, (unsigned char)255, (unsigned char)255 });

	}
}


void CPush::SetOwner(IEntity* _owner)
{
	if (owner)
		owner->Release();

	owner = _owner;

	if (owner)
		owner->AddRef();
}

void CPush::HandleCollision(IEntity* other)
{
	if (other == owner)
		return;
	SGD::Vector forward = {0,-1};
	forward.Rotate(rotation);
	SGD::Vector dir = other->GetPosition() - position;
	dir.Normalize();
	float angleBetween = dir.ComputeAngle(forward);
	if (radius < dir.ComputeAngle(forward))
	{
		return;
	}
	if (radius < SGD::PI * 2)
		dir.Rotate(angleBetween / 2);

	//float mass = other->GetSize().width * other->GetSize().height;
	other->AddGravity(dir * strength);
}