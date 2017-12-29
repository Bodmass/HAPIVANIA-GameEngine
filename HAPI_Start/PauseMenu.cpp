#include "PauseMenu.h"
#include "Game.h"

PauseMenu::~PauseMenu()
{
	delete[] BG;
	delete[] Upgrade1;
	delete[] Upgrade2;
	delete[] Upgrade3;
}

void PauseMenu::update()
{
	bool PauseHit = false;

	if (game_->getController().digitalButtons[HK_DIGITAL_SELECT] || game_->getKeyboard().scanCode[HK_ESCAPE])
		PauseHit = true;


	if (PauseHit && !game_->getPauseLock())
	{
		justopened = true;
		game_->setPauseLock(true);
		if(game_->getRoom() == "Demo")
			game_->switchScene_Game();
		if (game_->getRoom() == "Boss")
			game_->switchScene_Boss();
	}

	if (!PauseHit)
	{
		game_->setPauseLock(false);
	}

}

void PauseMenu::render()
{
	if (justopened)
	{
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
		if (game_->p_SprintU_Get())
			game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), Upgrade1, 0, 0, game_->getCameraX(), game_->getCameraY());
		if (game_->p_SuperJump_Get())
			game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), Upgrade2, 0, 0, game_->getCameraX(), game_->getCameraY());
		if (game_->p_XRAYB_Get())
			game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), Upgrade3, 0, 0, game_->getCameraX(), game_->getCameraY());
		justopened = false;
	}


}

void PauseMenu::loadTextures()
{
	BG = new Texture("Textures/UI/Pause/PauseBG.png");
	Upgrade1 = new Texture("Textures/UI/Pause/PauseSprint.png");
	Upgrade2 = new Texture("Textures/UI/Pause/PauseJump.png");
	Upgrade3 = new Texture("Textures/UI/Pause/PauseXRAY.png");
}

void PauseMenu::loadGameObject()
{
}
