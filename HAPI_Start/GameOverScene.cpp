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

	if (game_->getKeyboard().scanCode['R'])
	{
		Sound::stopMusic("GameOver");
		game_->SetReset(true);
		game_->switchScene_Title();
	}
}

void GameOverScene::render()
{
	game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), BG, 0, 0, game_->getCameraX(), game_->getCameraY());
}

void GameOverScene::loadTextures()
{
	BG = new Texture("Textures/TitleScreen/Gameover.tga");
}

void GameOverScene::loadGameObject()
{
}

void GameOverScene::loadSounds()
{
	Sound::addMusic("GameOver", "Audio/BGM/GameOver.ogg");
}
