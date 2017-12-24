#include "EndScene.h"
#include "Game.h"



EndScene::~EndScene()
{
	for (auto* gameObject : gameObjects)
	{
		delete gameObject;
	}
}

void EndScene::update()
{


	if (!BGMPlaying)
	{
		Sound::playMusic("Title");
		game_->setCamera(0, 0);
		BGMPlaying = true;
	}

	creditstext1->setY(creditstext1->getY() - 1);

	if (creditstext2->getY() >= 0)
	{
		creditstext2->setY(creditstext2->getY() - 1);
	}

}

void EndScene::render()
{
	if (fadecount < 30)
	{
		fadecount++;
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), game_->getGraphics().getSprite("Fade"), 0, 0, game_->getCameraX(), game_->getCameraY());
	}

	for (auto* gameObject : gameObjects)
	{

		if (gameObject->getTexture()->getAlpha())
			game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), gameObject->getTexture(), gameObject->getX(), gameObject->getY(), game_->getCameraX(), game_->getCameraY());
		else
			game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), gameObject->getTexture(), gameObject->getX(), gameObject->getY(), game_->getCameraX(), game_->getCameraY());
	}

}

void EndScene::loadTextures()
{
	game_->getGraphics().loadTexture("Fade", "Textures/UI/Credits/Fade.png");
	game_->getGraphics().loadTexture("Credits1", "Textures/UI/Credits/Credits.png");
	game_->getGraphics().loadTexture("Credits2", "Textures/UI/Credits/EndText.png");

}

void EndScene::loadGameObject()
{
	creditstext1 = new GameObject(game_->getGraphics().getSprite("Credits1"), Rectangle(game_->getGraphics().getSprite("Credits1")->getWidth(), game_->getGraphics().getSprite("Credits1")->getHeight()), 0, 720);
	creditstext2 = new GameObject(game_->getGraphics().getSprite("Credits2"), Rectangle(game_->getGraphics().getSprite("Credits2")->getWidth(), game_->getGraphics().getSprite("Credits2")->getHeight()), 0, 720 + game_->getGraphics().getSprite("Credits1")->getHeight());
	gameObjects.push_back(creditstext1);
	gameObjects.push_back(creditstext2);
}

void EndScene::loadSounds()
{
	//Sound::addMusic("Title", "Audio/BGM/Title.ogg");
}
