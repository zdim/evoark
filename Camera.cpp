#include "Camera.h"
#include "GameStates\LevelStates\ILevelState.h"
#include "GameStates\Game.h"
CCamera::CCamera(IEntity* t = nullptr, SGD::Size screen = SGD::Size{})
{
	if (!t)
	{
		t = Game::GetInstance()->GetLevelState()->GetPlayer();
	}
	target = t;
	t->AddRef();

	if (screen == SGD::Size())
	{
		screen.width = Game::GetInstance()->GetScreenWidth();
		screen.height = Game::GetInstance()->GetScreenHeight();
	}
	screenSize = screen;
	pos = target->GetPosition();
}

CCamera::~CCamera()
{
	target->Release();
}

void CCamera::Update(float dt)
{
	if (pos == target->GetPosition() - screenSize/2)
		return;
	
	SGD::Point tPos = target->GetPosition();
	//SGD::Vector mOffset = GetOffset();
	SGD::Vector mOffset = SGD::Vector{screenSize.width, screenSize.height}/-2;
	SGD::Point dest = tPos + mOffset;//target->GetPosition() + GetOffset();
	SGD::Vector dir = dest - pos;
	dir.Normalize();
	dir *= speed;
	pos	+= dir*dt;
}

void  CCamera::SetTarget(IEntity* t)
{
	if (!t)
		return;

	t->AddRef();
	target->Release();
	target = t;
}
