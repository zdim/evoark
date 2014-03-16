
#include "GameState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Graphics/Particles/Flyweight.h"
#include "../Graphics/Particles/Emitter.h"

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

CGameState* CGameState::GetInstance(void)
{
	static CGameState instance;
	return &instance;
}

void	CGameState::Enter(void)
{
	BackgroundImage = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/backgroundTmp.png");
	TestParticle = SGD::GraphicsManager::GetInstance()->LoadTexture("Resources/Graphics/test.png");

	dataParticleTest = new CFlyweight(TestParticle, { 0.4f, 0.4f }, { 0.1f, 0.1f },
		255, 127, 0, 0, 
		255, 255, 0, 0, 
		1, 1,
		35, 5, 35, 5);

	dataParticleTest2 = new CFlyweight(TestParticle, { 0.4f, 0.4f }, { 0.1f, 0.1f },
		255, 150, 0, 0,
		255, 1, 0, 1,
		1, 1,
		15, 5, 15, 5);


	SGD::Size tempSize = { 4, 4 };
	SGD::Point tempPosition = { 333, 333 };

	SGD::Size tempSize2 = { 3, 3 };
	SGD::Point tempPosition2 = { 150, 150 };


	testEmit = new CEmitter(dataParticleTest, tempSize, tempPosition, 150,0.01f,1.0f,true,30);
	testEmit2 = new CEmitter(dataParticleTest2, tempSize2, tempPosition2, 25, 0.3f, 0.3f,false,5);
	testEmit->Initialize();
	testEmit2->Initialize();
} 

void	CGameState::Exit(void)
{
	dataParticleTest = nullptr;
	delete dataParticleTest;
}

bool	CGameState::Input(void)
{
	return true;
}

void	CGameState::Update(float dt)
{
	testEmit->Update(dt);
	testEmit2->Update(dt);
}

void	CGameState::Render(void)
{
	
	SGD::GraphicsManager::GetInstance()->DrawTexture(BackgroundImage, testEmit->GetEmitterPosition());
	testEmit->Render();
	testEmit2->Render();
}
