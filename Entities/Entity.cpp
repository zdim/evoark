//
#include "Entity.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <algorithm>

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
	float scale = std::max(size.width/imageSize.width, size.height/imageSize.height);
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
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