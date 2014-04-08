//
#include "Module.h"
#include "../Ships/Enemies/Coral.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

CModule::CModule()
{
	owner = nullptr;
}


CModule::~CModule()
{
}

void CModule::SetOwner(CCoral* newVal)
{
	if (owner == newVal)
		return;

	if (owner)
		owner->Release();

	owner = newVal;

	if (owner)
		owner->AddRef();
}

void CModule::Update(float dt)
{
	if (damaged > 0)
		damaged -= dt;
	if (damaged < 0)
		damaged = 0;

	timer += dt;
	SGD::Vector rotatedOffset = posOffset;
	rotatedOffset.Rotate(owner->GetRotation());
	position = owner->GetPosition() + rotatedOffset;

	rotation = owner->GetRotation() + rotOffset;
}

void CModule::Render()
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

void CModule::TakeDamage(int damage, bool collision)
{
	damage -= owner->RequestShield(damage);
	if (collision)
		damage *= COLLISION_MODIFIER;
	hull -= damage;
	damaged = .15f;
	if (hull <= 0)
	{
		SelfDestruct();
	}
}

void CModule::Activate()
{

}

void CModule::ReleaseOwner()
{
	if (!owner)
		return;
	owner->Release();
}

void CModule::SelfDestruct()
{
	owner->DestroyModule(this);
}