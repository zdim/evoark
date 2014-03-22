#include "Button.h"
#include "SGD Wrappers\SGD_GraphicsManager.h"

void Button::Render(bool selected)
{
	SGD::GraphicsManager::GetInstance()->DrawRectangle(box, SGD::Color{});
}