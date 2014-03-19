#pragma once
#include "Copperhead.h"
#include "../../Leader.h"
class CMamba :
	public CCopperhead
{
public:
	CMamba();
	virtual ~CMamba();
};

class CMambaCoord : public CMamba, public Coordinator
{

};