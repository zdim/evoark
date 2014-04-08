#include "EventTrigger.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../GameStates/Game.h"

void EventTrigger::HandleCollision(IEntity* other)
{
	if (other->GetType() == (int)EntityType::Player)
	{
		colliding = true;
	}
	
}

void EventTrigger::Render()
{
	if (colliding)
	{
		SGD::Size screenSize = { (float)Game::GetInstance()->GetScreenWidth(), (float)Game::GetInstance()->GetScreenHeight() };
		SGD::GraphicsManager* graphics = SGD::GraphicsManager::GetInstance();
		switch (triggerType)
		{
		case (int)triggerID::tutMovement:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Basic Movement");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "WASD to move. Mouse to aim.");
			break;
		case (int)triggerID::tutLasers:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Lasers");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Left click to fire lasers.");
			break;
		case (int)triggerID::tutMissiles:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Missiles");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Right click to fire missiles.");
			break;
		case (int)triggerID::tutWarp:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Warp");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Hit Space to Warp.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Warping allows you to evade incoming fire.");
			break;
		case (int)triggerID::tutWell:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Well");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Hit Q to spawn a Gravity Well.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Gravity Well will suck in everything");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .70f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "of appropriate size.");
			break;
		case (int)triggerID::tutPush:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Push");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Hit E to use Gravity Push.");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Gravity Push will reflect everything");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .70f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "of appropriate size in an arc in front of you.");
			break;
		case (int)triggerID::tutCoordinator:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Coordinator");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Coordinators are responsible for enemy");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "back-up and distress calls. Kill them");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .70f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "to prevent ships from requesting back-up.");
			break;
		case (int)triggerID::tutHuman:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Human Ship");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Saving human ships from enemies will");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "cause for more human assistance in the");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .70f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "final battle.");
			break;
		case (int)triggerID::tutBoss:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Boss");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Each level has a boss and each boss");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "has a unique mechanic. Remember to use");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .70f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "your abilities!");
			break;
		case (int)triggerID::tutStargate:
			graphics->DrawRectangle(SGD::Rectangle{ { screenSize.width * .35f, screenSize.height * .6f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .15f } }, { 200, 0, 0, 0 }, { 200, 255, 255, 255 }, 2);
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .62f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "Stargate");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .66f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "After defeating a boss, the Stargate");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .68f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "opens. The Stargate will take you to");
			Game::GetInstance()->FontSmall.WriteCenter({ { screenSize.width * .35f, screenSize.height * .70f }, SGD::Size{ screenSize.width * .3f, screenSize.height * .05f } }, "the next level.");
			break;
		default:
			break;
		}
	}

	colliding = false;
}
