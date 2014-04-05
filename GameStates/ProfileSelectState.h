#include "IGameState.h"
#include <vector>
#include "GameplayState.h"
#include "../Menu.h"
#include "../BitmapFont/BitmapFont.h"

class CProfileSelectState : public IGameState
{
	enum class MyState { Idle, Transition, Menu, ConfirmOverwrite, ConfirmDelete, ConfirmTutorial };
	std::vector<saveData> profiles;

	float transTimer;
	float transDuration = 0.15f;

	int currentProfile = 0;
	int renderedProfile = 0;

	CMenu* confirm;
	CMenu* menu;
	MyState state;
	Fnt font;

	SGD::Point previous = SGD::Point{ -300,300};
	SGD::Point current = SGD::Point{ 300, 200 };
	SGD::Point next = SGD::Point{ 900, 300 };

	SGD::Size profileSize = SGD::Size{ 375, 200 };

	CProfileSelectState(){}
	~CProfileSelectState(){}
public:
	static CProfileSelectState* GetInstance();
	void Enter() override;
	void Exit() override;

	bool Input() override;
	void Update(float dt) override;
	void Render() override;

	void SeletionInput();
	void MenuInput();

	void TransitionRender();

	void LoadProfiles();
	saveData CreateProfile();
	void RenderProfile(int index, SGD::Point pos);
	void TutorialConfirmation();
};