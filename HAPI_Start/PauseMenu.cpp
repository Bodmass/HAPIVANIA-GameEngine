#include "PauseMenu.h"
#include "Game.h"

PauseMenu::~PauseMenu()
{
	delete[] BG;
}

void PauseMenu::update()
{
	if (game_->getKeyboard().scanCode[HK_ESCAPE] && !game_->getPauseLock())
	{
		game_->setPauseLock(true);
		game_->switchScene_Game();
	}

	if (!game_->getKeyboard().scanCode[HK_ESCAPE])
	{
		game_->setPauseLock(false);
	}

}

void PauseMenu::render()
{
	game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
}

void PauseMenu::loadTextures()
{
	BG = new Texture("Textures/UI/Pause/PauseBG.tga");
}

void PauseMenu::loadGameObject()
{
}
