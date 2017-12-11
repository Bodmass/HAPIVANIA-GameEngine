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
		game_->getAudio().playMusic("Title");
		BGMPlaying = true;
	}

	if (game_->getKeyboard().scanCode[HK_RETURN])
	{
		game_->getAudio().stopMusic("Title");
		game_->switchScene_Game();
	}


}

void TitleScreen::render()
{
	game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
	HAPI.RenderText((game_->getScreenWidth() / 2)-30, game_->getScreenHeight() / 2, HAPI_TColour::WHITE, "Play", 30);
}

void TitleScreen::loadTextures()
{
	BG = new Texture("Textures/TitleScreen/Logo.tga");
}

void TitleScreen::loadGameObject()
{
}

void TitleScreen::loadSounds()
{
	game_->getAudio().addMusic("Title", "Audio/BGM/Title.ogg");
}
