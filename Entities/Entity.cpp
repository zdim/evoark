//
#include "Entity.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"

#define GRAVDECAY 0.75F

CEntity::CEntity()
{

}


CEntity::~CEntity()
{

}

void	CEntity::Update(float dt)
{
	position += (gravVec + velocity) * dt;
	gravVec *= GRAVDECAY;
}

void	CEntity::Render()
{
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, (position - size / 2), rotation, size / 2);
}

void	CEntity::HandleCollision()
{
	//Should never collide with anything.
	//TODO: Review catch/throw, and throw an error here
}

void	CEntity::AddRef()
{
	refCount++;
}

void	CEntity::Release()
{
	refCount--;
	if (refCount <= 0)
	{
		delete this;
	}
}