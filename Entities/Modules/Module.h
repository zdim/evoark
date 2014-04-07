#pragma once
#include "../Entity.h"
//#include "../Ships/Enemies/Coral.h"
class CCoral;

class CModule :
	public CEntity
{
protected:
	CCoral* owner;
	SGD::Vector posOffset; //Offset by owner's position
	float rotOffset = 0;
	float cooldown;		//For any abilities and shield delay
	float timer = 0;	//For cooldown
	int hull = 50;		//For destruction
	int hullMax = 50;
	int tier = 0;
public:
	CModule();
	virtual ~CModule();

	virtual bool IsTurret() {return false;}
	int GetType() { return (int)EntityType::BaseModule; }
	CCoral*	GetOwner() { return owner; }
	SGD::Vector GetOffset() {return posOffset;}
	float		GetCooldown() { return cooldown; }		//For any abilities and shield delay
	float		GetTimer() { return timer; }	//For cooldown
	int			GetHull() { return hull; }		//For destruction
	int			GetHullMax() { return hullMax; }
	int			GetTier() {return tier;}
	void SetOwner (CCoral* newVal);// { owner = newVal; owner->AddRef(); }
	void SetOffset(SGD::Vector newVal) {posOffset = newVal; }
	void SetCooldown (float newVal) { cooldown = newVal; }		//For any abilities and shield delay
	void SetTimer (float newVal) { timer = newVal; }	//For cooldown
	void SetHull(int newVal) { hull = newVal; }		//For destruction
	void SetHullMax (int newVal) { hullMax = newVal; }
	void SetTier(int newTier) {tier = newTier;}

	virtual void Update(float dt) override;

	virtual void TakeDamage(int damage, bool collision = false);
	virtual void Activate();
	virtual void SelfDestruct() override;

	void ReleaseOwner();
};

