#include "CreateGameOverMessage.h"
#include "../GameStates/Game.h"
#include "../GameStates/LevelStates/GameOverState.h"

CCreateGameOverMessage::CCreateGameOverMessage() : Message(MessageID::GameOver)
{
	Game::GetInstance()->PushState(CGameOverState::GetInstance());
}


CCreateGameOverMessage::~CCreateGameOverMessage()
{
}
