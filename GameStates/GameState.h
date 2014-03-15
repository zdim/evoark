#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_Handle.h"
class CFlyweight;
class CEmitter;

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

	SGD::HTexture BackgroundImage;
	SGD::HTexture TestParticle;
	CFlyweight    *dataParticleTest;
	CEmitter      *testEmit;

	CFlyweight    *dataParticleTest2;
	CEmitter      *testEmit2;

};

