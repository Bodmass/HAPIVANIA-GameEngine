#include "PauseMenu.h"
#include "Game.h"

PauseMenu::~PauseMenu()
{
	delete[] BG;
	delete[] Upgrade1;
	delete[] Upgrade2;
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
	if(game_->p_SprintU_Get())
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), Upgrade1, 0, 0, game_->getCameraX(), game_->getCameraY());
	if (game_->p_SuperJump_Get())
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), Upgrade2, 0, 0, game_->getCameraX(), game_->getCameraY());
}

void PauseMenu::loadTextures()
{
	BG = new Texture("Textures/UI/Pause/PauseBG.tga");
	Upgrade1 = new Texture("Textures/UI/Pause/PauseSprint.png");
	Upgrade2 = new Texture("Textures/UI/Pause/PauseJump.png");
}

void PauseMenu::loadGameObject()
{
}