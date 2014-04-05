#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"
#include "../Entities/EntityManager.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Color.h"
#include "../Entities/Ships/Player.h"
#include <vector>
#include <string>
#include "../Graphics/Particles/ParticleSystem.h"
#include "../SGD Wrappers/SGD_Message.h"
#include "LevelStates\ILevelState.h"
#include "../Camera.h"
#include "../SoundBox.h"

class CFlyweight;
class CEmitter;
class CParticleSystem;
class CPlayer;

class CTestLevelState :
	public ILevelState
{
public:
	static CTestLevelState* GetInstance(void);


	virtual void	Enter(void)				override;
	virtual void	Exit(void)				override;
	virtual bool	Input(void)				override;
	virtual void	Update(float dt)	override;
	virtual void	Render(void)				override;
	static void MessageProc(const SGD::Message* msg);
	IEntity* GetPlayer();
	CCamera* GetCam() {return cam;}

	SGD::Size GetWorldSize() { return SGD::Size{ float(m_nNumQuadsWidth * m_nQuadWidth), float(m_nNumQuadsHeight * m_nQuadHeight) }; }
	bool GetBossStatus() override { return m_bBossKilled; }

	void Save();
	void Load();

private:
	CTestLevelState();
	virtual ~CTestLevelState();

	int m_nScreenHeight = 0;
	int m_nScreenWidth = 0;
	SGD::HTexture BackgroundImage;
	SGD::HTexture backgroundBlack;
	SGD::HTexture backgroundNebula = SGD::INVALID_HANDLE;
	SGD::HTexture backgroundStars = SGD::INVALID_HANDLE;
	SGD::HTexture backgroundStars1 = SGD::INVALID_HANDLE;
	SGD::HTexture backgroundStars2 = SGD::INVALID_HANDLE;
	SGD::Point nebulaPos = SGD::Point{ 0, 0 };
	SGD::Point starsPos = SGD::Point{ 0, 0 };
	SGD::Point stars1Pos = SGD::Point{ 0, 0 };
	SGD::Point stars2Pos = SGD::Point{ 0, 0 };

	CEntityManager* EntityManager;
	SGD::GraphicsManager* graphics;
	bool m_bBossKilled = false; 
	CSoundBox* soundBox = nullptr;


	CEntity* player = nullptr;
	CCamera* cam;
	std::string    testing;
	bool           m_bLoaded;
	int            m_nLine;

	// level creation
	enum Objects { PLAYER, COPPERHEAD, COBRA, MAMBA, CORAL, MOCASSIN, ASTEROID, PLANET, HUMAN, COORDINATOR, NONE, NUM_OBJECTS };

	struct Quadrant
	{
		int x;
		int y;
		int possibleObjects;
		Objects objType;
		int objectAmount;
		bool randomized;
		SGD::Point pos = SGD::Point{ 0, 0 };
	};

	struct Event
	{
		SGD::Rectangle area = { 0, 0, 0, 0 };
		std::string eType;
	};

	void		Generate();
	int m_nQuadWidth = 0;
	int m_nQuadHeight = 0;
	int m_nNumQuadsWidth = 0;
	int m_nNumQuadsHeight = 0;

	typedef std::vector<Quadrant> QuadCol;
	typedef std::vector<QuadCol> World;
	//QuadRow quadRow;
	World world;
	
	std::vector<Event> events;
	std::vector<SGD::Rectangle> collisionRects;

	// xml test
	bool	LoadXMLLevel(const char* pXMLFile);
	
	

	CParticleSystem pSystem;


	// UI rendering
	void UI(CPlayer* _player, std::vector<IEntity*> _allies, IEntity* _coordinator, IEntity* _stargate);
	SGD::HTexture objArrow = SGD::INVALID_HANDLE;
};

