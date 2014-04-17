#pragma once
#include "GravityProjectile.h"
class CPush :
	public CGravityProjectile
{
	SGD::Vector forward;
	IEntity* owner = nullptr;

	int tier = 0;

	float life = 0.f;
	float alpha = 0.f;

	SGD::HTexture pushZero = SGD::INVALID_HANDLE;
	SGD::HTexture pushOne = SGD::INVALID_HANDLE;
	SGD::HTexture pushTwo = SGD::INVALID_HANDLE;
	SGD::HTexture pushThree = SGD::INVALID_HANDLE;

public:
	CPush();
	virtual ~CPush();
	void Render();
	void Update(float dt);
	void SetOwner(IEntity* _owner);
	int GetType() override { return (int)EntityType::Push; }
	SGD::Vector GetForward() {return forward;}
	void SetForward(SGD::Vector newForward) {forward = newForward;}
	void HandleCollision(IEntity* other) override;
	void SetTier(int _tier) { tier = _tier; }
};

