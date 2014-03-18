#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "../Entities/EntityManager.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Color.h"
#include <vector>
#include <string>
#include "../Graphics/Particles/ParticleSystem.h"

class CFlyweight;
class CEmitter;
class CParticleSystem;


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
	//CEntityManager EnitityManager;
	SGD::GraphicsManager* graphics;

	// level creation
	enum Objects { PLAYER, COPPERHEAD, COBRA, MAMBA, CORAL, MOCASSIN, ASTEROID, NONE, NUM_OBJECTS };

	struct enemy
	{
		SGD::Point pos;
		SGD::Size size;
		SGD::Color col;
		Objects type;
	};

	struct Quadrant
	{
		int x;
		int y;
		int possibleObjects;
		Objects objType;
		int objectAmount;
	};

	void		Generate();
	int m_nQuadWidth = 0;
	int m_nQuadHeight = 0;
	int m_nNumQuadsWidth = 0;
	int m_nNumQuadsHeight = 0;
	std::vector<enemy> enemies;

	typedef std::vector<Quadrant> QuadCol;
	typedef std::vector<QuadCol> World;
	//QuadRow quadRow;
	World world;
	



	// xml test
	bool	LoadXMLLevel(const char* pXMLFile);
	
	

	CParticleSystem pSystem;


};

