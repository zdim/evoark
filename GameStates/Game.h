
/***************************************************************
|	File:		Game.h
|	Author:		Jonathan Sullivan
|	Course:		SGD 1401
|	Purpose:	Game class controls the SGD wrappers
|				& runs the game state machine
***************************************************************/

#ifndef GAME_H
#define GAME_H


/**************************************************************/
// Forward class declaration
//	- tells the compiler that the type exists
//	- allows us to create pointers or references
class BitmapFont;
class IGameState;

#define FONT_SIZE 32.0f

#include "../SGD Wrappers/SGD_Declarations.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Handle.h"
//#include <deque>
#include <vector>
#include "../BitmapFont/BitmapFont.h"
#include "LevelStates\ILevelState.h"

class CParticleSystem;

/**************************************************************/
// Game class
//	- runs the game logic
//	- controls the SGD wrappers
//	- SINGLETON!
//		- there is only ONE instance
//		- global access method (GetInstance)
class Game
{
public:
	/**********************************************************/
	// Singleton Accessors:
	static Game*	GetInstance(void);
	static void		DeleteInstance(void);


	/**********************************************************/
	// Setup, Play, Cleanup:
	bool Initialize(int width, int height);
	int	 Main(void);
	void Terminate(void);


	/**********************************************************/
	// Screen Size Accessors:
	int	GetScreenWidth(void) const	{ return m_nScreenWidth; }
	int	GetScreenHeight(void) const	{ return m_nScreenHeight; }

	// Font Accessor:
	//SGD::HAudio GetMusic(void) const{return m_hSfxMusic;}
	//int			GetVolMusic(void)	{ return m_nVolMusic; }
	//int			GetVolSound(void) { return m_nVolSound; }
	//void		SetVolMusic(int vol) { m_nVolMusic = vol; }
	//void		SetVolSound(int vol) { m_nVolSound = vol; }
	//void		ModVolMusic(int vol) { m_nVolMusic += vol; }
	//void		ModVolSound(int vol) { m_nVolSound += vol; }


	/**********************************************************/
	// Game State Machine:
	//	- can ONLY be called by the state's Input, Update, or Render methods!!!
	//void ChangeState(IGameState* pNewState);
	//Stackbased - Needs Push and Pop
	bool PushState(IGameState* newState);
	void PopState();

	ILevelState* GetLevelState();

	/**********************************************************/
	// Game Font
	Fnt				Font;
private:
	/**********************************************************/
	// Singleton Object:
	static Game*	s_pInstance;

	Game(void) = default;		// default constructor
	~Game(void) = default;		// destructor

	Game(const Game&) = delete;	// copy constructor
	Game& operator= (const Game&) = delete;	// assignment operator

	void Load(void);
	/**********************************************************/
	// SGD Wrappers
	SGD::AudioManager*		m_pAudio = nullptr;
	SGD::GraphicsManager*	m_pGraphics = nullptr;
	SGD::InputManager*		m_pInput = nullptr;
    CParticleSystem*        m_pParticleSystem = nullptr;



	/**********************************************************/
	// options.txt
	//SGD::HAudio				m_hSfxMusic		= SGD::INVALID_HANDLE;
	//int						m_nVolMusic		= 100;
	//int						m_nVolSound		= 100;

	/**********************************************************/
	// Screen Size
	int						m_nScreenWidth = 1;
	int						m_nScreenHeight = 1;



	/**********************************************************/
	// Current Game State
	std::vector<IGameState*>	m_qStates;


	/**********************************************************/
	// Game Time
	unsigned long			m_ulGameTime = 0;

	//Fullscreen/Windowed:
	bool m_bWindowed = true;
};

#endif //GAME_H