#pragma once
#include "Coral.h"
class CMoccasin :
	public CCoral
{
public:
	CMoccasin();
	virtual ~CMoccasin();

	void SelfDestruct() override;
	unsigned int GetModuleCount() { return modules.size(); }
	void AddModule();
};