#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Color.h"
#include <vector>
#include <string>

class CGameState :
	public IGameState
{
public:
	static CGameState* GetInstance(void);

	virtual void	Enter(void)				override;
	virtual void	Exit(void)				override;
	virtual bool	Input(void)				override;
	virtual void	Update(float dt)	override;
	virtual void	Render(void)				override;

private:

	CGameState();
	virtual ~CGameState();

	int m_nScreenHeight = 0;
	int m_nScreenWidth = 0;
	SGD::HTexture BackgroundImage;

	// level creation

	struct enemy
	{
		SGD::Rectangle pos;
		SGD::Color col;
		std::string type;
	};

	void		Generate();
	int m_nQuadWidth = 0;
	int m_nQuadHeight = 0;
	std::vector<enemy> enemies;
	
	struct Quadrant
	{
		int x;
		int y;
		std::string objectType;
		int objectAmount;

	};

	// xml test
	bool	LoadXMLLevel(const char* pXMLFile);
};

