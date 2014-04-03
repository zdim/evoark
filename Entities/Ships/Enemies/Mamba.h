#pragma once
#include "Copperhead.h"
#include "../../Leader.h"
class CMamba :
	public CCopperhead
{
private:
	

public:
	CMamba();
	virtual ~CMamba();
	int GetType() override { return (int)EntityType::Mamba; }
	void Update(float dt);
	void CreateMissile();
};

class CMambaCoord : public CMamba, public Coordinator
{
	virtual ~CMambaCoord(){}
};

