#pragma once
#include "../Entity.h"
class CModule :
	public CEntity
{
protected:
	IEntity* owner;
	SGD::Vector posOffset; //Offset by owner's position
	float rotOffset = 0;
	float cooldown;		//For any abilities and shield delay
	float timer = 0;	//For cooldown
	int hull = 50;		//For destruction
	int hullMax = 50;
public:
	CModule();
	virtual ~CModule();

	int GetType() { return (int)EntityType::BaseModule; }
	IEntity*	GetOwner() { return owner; }
	SGD::Vector GetOffset() {return posOffset;}
	float		GetCooldown() { return cooldown; }		//For any abilities and shield delay
	float		GetTimer() { return timer; }	//For cooldown
	int			GetHull() { return hull; }		//For destruction
	int			GetHullMax() { return hullMax; }

	void SetOwner (IEntity*	newVal);// { owner = newVal; owner->AddRef(); }
	void SetOffset(SGD::Vector newVal) {posOffset = newVal; }
	void SetCooldown (float newVal) { cooldown = newVal; }		//For any abilities and shield delay
	void SetTimer (float newVal) { timer = newVal; }	//For cooldown
	void SetHull (int newVal) { hull = newVal; }		//For destruction
	void SetHullMax (int newVal) { hullMax = newVal; }

	virtual void Update(float dt) override;

	virtual void TakeDamage(int damage, bool collision = false);
	virtual void Activate();

	void ReleaseOwner();
};

