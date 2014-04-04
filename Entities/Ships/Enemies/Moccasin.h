#pragma once
#include "Coral.h"
class CMoccasin :
	public CCoral
{
private:

	int m_nLevel;



public:
	CMoccasin();
	virtual ~CMoccasin();
	void Init(int i);
	void SelfDestruct() override;
	unsigned int GetModuleCount() { return modules.size(); }
	void AddModule();
	virtual int GetType() override { return (int)EntityType::Moccasin; }
};