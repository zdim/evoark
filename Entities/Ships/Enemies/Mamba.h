#pragma once
#include "Copperhead.h"
#include "../../Leader.h"
class CMamba :
	public CCopperhead
{
private:
	CEmitter* m_Engine;
	SGD::Point  enginePos;
	CEmitter* m_Engine2;
	SGD::Point  enginePos2;
	CEmitter* m_Engine3;
	SGD::Point  enginePos3;

public:
	CMamba();
	virtual ~CMamba();
	int GetType() override { return (int)EntityType::Mamba; }
	void Render();
	void Update(float dt);
	void CreateMissile();
};

class CMambaCoord : public CMamba, public Coordinator
{
	virtual ~CMambaCoord(){}
	bool IsCoordinator() override {return true;}
	void SelfDestruct() override {
		if (!destroying) { CMamba::SelfDestruct(); Coordinator::Unregister(); }
	}
};

