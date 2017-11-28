#include "GameScene.h"
#include "Game.h"
#include "CollisionDetection.h"

GameScene::GameScene(Game* game)
{
	game_ = game;
}


GameScene::~GameScene()
{
	for (auto* gameObject : gameObjects)
	{
		delete gameObject;
	}
}


void GameScene::update()
{
		gameClock = HAPI.GetTime();

		for (auto* gameObject : gameObjects)
		{

			if (gameObject->getTexture()->getAlpha())
				game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), gameObject->getTexture(), gameObject->getX(), gameObject->getY(), game_->getCameraX(), game_->getCameraY());
			else
				game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), gameObject->getTexture(), gameObject->getX(), gameObject->getY(), game_->getCameraX(), game_->getCameraY());
		}
		/*
		if (controllerData.isAttached)
		{

		HAPI.RenderText(screenWidth - 130, 0, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2, "is Attached!", 22);

		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
		graphics.getSprite(1)->getPosY() += 1;
		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_UP])
		graphics.getSprite(1)->getPosY() -= 1;
		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_LEFT])
		graphics.getSprite(1)->getPosX() -= 1;
		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_RIGHT])
		graphics.getSprite(1)->getPosX() += 1;

		if (graphics.getSprite(1)->getPosY() > screenHeight / 2 - 100 && graphics.getSprite(1)->getPosY() < screenHeight / 2 + 100)
		{
		if (graphics.getSprite(1)->getPosX() > screenWidth / 2 - 100 && graphics.getSprite(1)->getPosX() < screenWidth / 2 + 100)
		HAPI.SetControllerRumble(0, 15000, 15000);
		else
		HAPI.SetControllerRumble(0, 0, 0);
		}
		else
		HAPI.SetControllerRumble(0, 0, 0);
		}
		*/



		if (game_->getKeyboard().scanCode[HK_LSHIFT] && player)
			playerSpeed = 2;
		else
			playerSpeed = 1;

		Rectangle player2;
		if (player)
		{
			
			player2 = Rectangle(game_->getGraphics().getSprite(1)->getWidth(), game_->getGraphics().getSprite(1)->getHeight());
			player2.Move(player->getX() + 1, player->getY());

		}
		
		col = false;

		for (int i = 0; i < platforms.size(); i++)
		{
			if (CollisionDetection::CheckCollision(player2, platforms[i]))
			{
				col = true;
				break;
			}

		}

		if (!col && !player_isJumping && player)
		{
			player->setY(player->getY() + playerSpeed);
		}

		if (game_->getKeyboard().scanCode['A'] && player)
		{
			//if(!col)
			//{

				player->setX(player->getX() - playerSpeed);
				if (player->getX() > game_->getScreenWidth() / 2)
					game_->setCamera(playerSpeed, 0);
				else
					game_->setCamera(0, 0);
			//}

		}

		if (game_->getKeyboard().scanCode['D'] && player)
		{

			//if (!col)
			//{
				player->setX(player->getX() + playerSpeed);
				if (player->getX() > game_->getScreenWidth() / 2)
					game_->setCamera(-playerSpeed, 0);
				else
					game_->setCamera(0, 0);
			//}

		}//85,359

		if ((game_->getKeyboard().scanCode['W'] || game_->getKeyboard().scanCode[HK_SPACE]) && player)
		{
			if (!player_isJumping)
				player_Jump();

		}
		if (player_isJumping && player)
			player_Jump();

		if (player && platforms.size() >= 2)
		{
			player->getRect().Move(player->getX(), player->getY());
			platforms[0].Move(platform1->getX(), platform1->getY());
			platforms[1].Move(platform2->getX(), platform2->getY());
		}
		/*
		if (keyData.scanCode[HK_DOWN])
			CamY += playerSpeed;
		if (keyData.scanCode[HK_UP])
			CamY -= playerSpeed;
		if (keyData.scanCode[HK_LEFT])
			CamX -= playerSpeed;
		if (keyData.scanCode[HK_RIGHT])
			CamX += playerSpeed;
		*/
	/*
	delete[] screenRect;
	delete[] playerRect;
	delete[] platformRect;
	isRunning = false;
	*/
}

void GameScene::loadTextures()
{
	game_->getGraphics().loadTexture("Data/BG.tga", false); //0 - BG -
	game_->getGraphics().loadTexture("Data/PlayerTest.tga"); //1 - Player - 
	game_->getGraphics().loadTexture("Data/test.tga", false); //2 - Platform 1 -
	game_->getGraphics().loadTexture("Data/platform1.tga", false); //3 - Platform 2 - 
}

void GameScene::loadGameObject()
{
	BG = new GameObject(game_->getGraphics().getSprite(0), Rectangle(game_->getGraphics().getSprite(0)->getWidth(), game_->getGraphics().getSprite(0)->getHeight()), 0, 0, true);
	player = new GameObject(game_->getGraphics().getSprite(1), Rectangle(game_->getGraphics().getSprite(1)->getWidth(), game_->getGraphics().getSprite(1)->getHeight()), 85, 359);
	platform1 = new GameObject(game_->getGraphics().getSprite(2), Rectangle(game_->getGraphics().getSprite(2)->getWidth(), game_->getGraphics().getSprite(2)->getHeight()), 0, 400);
	platform2 = new GameObject(game_->getGraphics().getSprite(3), Rectangle(game_->getGraphics().getSprite(3)->getWidth(), game_->getGraphics().getSprite(3)->getHeight()), 300, 300);

	gameObjects.push_back(BG);
	gameObjects.push_back(player);
	gameObjects.push_back(platform1);
	gameObjects.push_back(platform2);

	platforms.push_back(platform1->getRect());
	platforms.push_back(platform2->getRect());
}

void GameScene::player_Jump()
{
	if (!player_isJumping)
	{
		player_isJumping = true;
		jumping_time = gameClock + 750;

	}

	if (player_isJumping)
	{
		if (gameClock > jumping_time)
		{

			if (col)
			{
				player_isJumping = false;
				player->setY(player->getY() - playerSpeed);
			}
			else
				player->setY(player->getY() + playerSpeed);
		}
		else
		{
			player->setY(player->getY() - playerSpeed);
			if (col)
			{
				jumping_time = gameClock - 1;
			}
		}
			
	}
}


