 #pragma once
#include "Coral.h"

class CRepairStation;

class CMoccasin :
	public CCoral
{
private:

	int m_nLevel;
	float m_fTimer;
	float m_fAsteroidCD;
	float m_fShipCD;
	int   m_nNumberOfShips;
	bool  m_bStationsUP;
	std::vector<CRepairStation*> stations;

public:
	CMoccasin();
	virtual ~CMoccasin();
	void Init(int i);
	void Update(float dt);
	void SelfDestruct() override;
	unsigned int GetModuleCount() { return modules.size(); }
	void AddModule();
	virtual int GetType() override { return (int)EntityType::Moccasin; }
	int GetLevel() { return m_nLevel; }
	std::vector<CRepairStation*> GetStations() { return stations; }
	int GetShipNumbers() { return m_nNumberOfShips; }
};