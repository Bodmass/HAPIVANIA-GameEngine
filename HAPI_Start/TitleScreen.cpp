#include "TitleScreen.h"
#include "Game.h"



TitleScreen::~TitleScreen()
{
	delete[] BG;
}

void TitleScreen::update()
{
	game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());

	if (!BGMPlaying)
	{
		HAPI.PlayStreamedMedia("Audio/BGM/Title.ogg");
		BGMPlaying = true;
	}

	if (game_->getKeyboard().scanCode[HK_RETURN])
	{
		HAPI.StopStreamedMedia(0);
		game_->switchScene_Game();
	}

	HAPI.RenderText(400, game_->getScreenHeight()/2, HAPI_TColour::WHITE, "Play", 30);
}

void TitleScreen::loadTextures()
{
	BG = new Texture("Textures/TitleScreen/Logo.tga");
}

void TitleScreen::loadGameObject()
{
}