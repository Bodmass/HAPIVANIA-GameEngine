#include "GameOverScene.h"
#include "Game.h"


GameOverScene::~GameOverScene()
{
	delete[] BG;
}

void GameOverScene::update()
{
	gameClock = HAPI.GetTime();
	if(!setup)
	{ 
		
		delayClock = gameClock + 1500;
		setup = true;
	}

	if (gameClock > delayClock)
	{
		if (!BGMPlaying)
		{
			Sound::playMusic("GameOver");
			BGMPlaying = true;
		}
	}

	/*
	if (game_->getKeyboard().scanCode[HK_ESCAPE])
	{
		Sound::stopMusic("GameOver");
		game_->switchScene_Title();
	}
	*/
}

void GameOverScene::render()
{
	game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
	HAPI.RenderText((game_->getScreenWidth() / 2) - 30, game_->getScreenHeight() / 2, HAPI_TColour::WHITE, "You have died... :'(", 30);
}

void GameOverScene::loadTextures()
{
	BG = new Texture("Textures/TitleScreen/Logo.tga");
}

void GameOverScene::loadGameObject()
{
}

void GameOverScene::loadSounds()
{
	Sound::addMusic("GameOver", "Audio/BGM/GameOver.ogg");
}
