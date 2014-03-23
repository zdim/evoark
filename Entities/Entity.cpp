//
#include "Entity.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <algorithm>
#include "../Camera.h"
#include "../GameStates/LevelStates/ILevelState.h"
#include "../GameStates/Game.h"

#define GRAVDECAY 0.025F

CEntity::CEntity()
{

}


CEntity::~CEntity()
{

}

SGD::Point CEntity::offsetToCamera()
{
	return position - size / 2 + Game::GetInstance()->GetLevelState()->GetCam()->GetOffset();
}

void	CEntity::Update(float dt)
{
	position += (velocity) * dt;
	position += gravVec * dt;
	float gravSpeed = gravVec.ComputeLength();
	float mySpeed = velocity.ComputeLength();
	if (gravVec != SGD::Vector{ 0, 0 })
	{
		gravVec -= (gravVec * GRAVDECAY);
		if (gravVec.ComputeLength() <= 2)
		{
			gravVec = SGD::Vector{0,0};
		}
	}
}

void	CEntity::Render()
{
	float scale = std::max(size.width/imageSize.width, size.height/imageSize.height);
	CCamera* cam = Game::GetInstance()->GetLevelState()->GetCam();
	//SGD::GraphicsManager::GetInstance()->DrawTextureSection(image, position - size/2, SGD::Rectangle(SGD::Point{0,0},imageSize), rotation, imageSize / 2, SGD::Color{}, SGD::Size{scale, scale});
	SGD::Point renderPoint = offsetToCamera();
	SGD::GraphicsManager::GetInstance()->DrawTexture(image, renderPoint, rotation, imageSize / 2, {}, { scale, scale });
}

void	CEntity::HandleCollision(IEntity* other)
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