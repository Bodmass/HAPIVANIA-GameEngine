#include "TitleScreen.h"
#include "Game.h"



TitleScreen::~TitleScreen()
{
	delete[] BG;
}

void TitleScreen::update()
{
	

	if (!BGMPlaying)
	{
		Sound::playMusic("Title");
		BGMPlaying = true;
	}

	if (game_->getKeyboard().scanCode[HK_RETURN] || game_->getController().digitalButtons[HK_DIGITAL_START])
	{
		Sound::stopMusic("Title");
		game_->switchScene_Game();
	}


	//Press Select (Controller) or the Escape Key to Change Difficulty Mode
	if (!dSwitchLock)
	{
		if (game_->getKeyboard().scanCode[HK_ESCAPE] || game_->getController().digitalButtons[HK_DIGITAL_SELECT])
		{
			dSwitchLock = true;
			if (game_->getDifficulty() == "Easy")
			{
				game_->setHardMode();
				return;
			}
			if (game_->getDifficulty() == "Hard")
			{
				game_->setEasyMode();
				return;
			}
		}
	}

	//Waits Until Select (Controller) or the Escape Key is released, for the Switch to be possible again
	if (!game_->getKeyboard().scanCode[HK_ESCAPE] && !game_->getController().digitalButtons[HK_DIGITAL_SELECT])
	{
		dSwitchLock = false;
	}

}

void TitleScreen::render()
{
	game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
	if (game_->getController().isAttached)
	{
		HAPI.RenderText((game_->getScreenWidth() / 2) - 140, game_->getScreenHeight() / 2, HAPI_TColour::WHITE, "PRESS [START] TO BEGIN", 30);
		if (game_->getDifficulty() == "Easy")
			HAPI.RenderText((game_->getScreenWidth() / 2) - 200, game_->getScreenHeight() / 2 + 30, HAPI_TColour::WHITE, "Easy Mode [SELECT TO CHANGE]", 30);
		if (game_->getDifficulty() == "Hard")
			HAPI.RenderText((game_->getScreenWidth() / 2) - 200, game_->getScreenHeight() / 2 + 30, HAPI_TColour::WHITE, "Hard Mode [SELECT TO CHANGE]", 30);
	}
	else
	{
		HAPI.RenderText((game_->getScreenWidth() / 2) - 150, game_->getScreenHeight() / 2, HAPI_TColour::WHITE, "PRESS [RETURN] TO BEGIN", 30);
		if (game_->getDifficulty() == "Easy")
			HAPI.RenderText((game_->getScreenWidth() / 2) - 200, game_->getScreenHeight() / 2 + 30, HAPI_TColour::WHITE, "Easy Mode [ESC TO CHANGE]", 30);
		if (game_->getDifficulty() == "Hard")
			HAPI.RenderText((game_->getScreenWidth() / 2) - 200, game_->getScreenHeight() / 2 + 30, HAPI_TColour::WHITE, "Hard Mode [ESC TO CHANGE]", 30);
	}
}

void TitleScreen::loadTextures()
{
	BG = new Texture("Textures/TitleScreen/Logo.tga");
	game_->getGraphics().loadTexture("LoadingScreen", "Textures/UI/Pause/LoadingBG.png", false);
}

void TitleScreen::loadGameObject()
{
}

void TitleScreen::loadSounds()
{
	Sound::addMusic("Title", "Audio/BGM/Title.ogg");
}
