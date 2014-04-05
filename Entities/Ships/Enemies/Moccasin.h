#pragma once
#include "Coral.h"
class CMoccasin :
	public CCoral
{
public:
	CMoccasin();
	virtual ~CMoccasin();

	int GetType(){ return (int)EntityType::Moccasin; }

	void SelfDestruct() override;
	unsigned int GetModuleCount() { return modules.size(); }
	void AddModule();
};