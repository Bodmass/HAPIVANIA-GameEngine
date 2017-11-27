#include "GameScene.h"
#include "Game.h"
#include "CollisionDetection.h"

GameScene::GameScene(Game* game)
{
	game_ = game;
}

/*
GameScene::GameScene(BYTE * newscreen) : screen(newscreen)
{
	screen = newscreen;
}*/

GameScene::~GameScene()
{

}


void GameScene::update()
{
		gameClock = HAPI.GetTime();

		//setColour(screen, 0, 0, 0, 255); //Clear screen to colour
		for (size_t i = 0; i < game_->getGraphics().getSpriteMap().size(); i++)
		{
			//if (graphics.getSprite(i)->getAlpha())
			if (game_->getGraphics().getSprite(i)->getAlpha())
				game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), game_->getGraphics().getSprite(i), game_->getCameraX(), game_->getCameraY());
			else
				game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), game_->getGraphics().getSprite(i), game_->getCameraX(), game_->getCameraY());
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



		if (game_->getKeyboard().scanCode[HK_LSHIFT])
			playerSpeed = 2;
		else
			playerSpeed = 1;

		Rectangle* player2;
		player2 = new Rectangle(game_->getGraphics().getSprite(1)->getWidth(), game_->getGraphics().getSprite(1)->getHeight());
		player2->Move(game_->getGraphics().getSprite(1)->getPosX() + 1, game_->getGraphics().getSprite(1)->getPosY() + 1);



		
		col = false;

		for (int i = 0; i < platforms.size(); i++)
		{
			if (CollisionDetection::CheckCollision(*player2, platforms[i]))
			{
				col = true;
				break;
			}

		}

		if (!col && !player_isJumping)
		{
			game_->getGraphics().getSprite(1)->getPosY() += playerSpeed;
		}

		if (game_->getKeyboard().scanCode['A'])
		{
			//if(!col)
			//{

				game_->getGraphics().getSprite(1)->getPosX() -= playerSpeed;
				if (game_->getGraphics().getSprite(1)->getPosX() > game_->getScreenWidth() / 2)
					game_->setCamera(playerSpeed, 0);
				else
					game_->setCamera(0, 0);
			//}

		}

		if (game_->getKeyboard().scanCode['D'])
		{

			//if (!col)
			//{
				game_->getGraphics().getSprite(1)->getPosX() += playerSpeed;
				if (game_->getGraphics().getSprite(1)->getPosX() > game_->getScreenWidth() / 2)
					game_->setCamera(-playerSpeed, 0);
				else
					game_->setCamera(0, 0);
			//}

		}//85,359

		if (game_->getKeyboard().scanCode['W'] || game_->getKeyboard().scanCode[HK_SPACE])
		{
			if (!player_isJumping)
				player_Jump();

		}
		if (player_isJumping)
			player_Jump();

		delete[] player2;

		playerRect.Move(game_->getGraphics().getSprite(1)->getPosX(), game_->getGraphics().getSprite(1)->getPosY());
		platforms[0].Move(game_->getGraphics().getSprite(2)->getPosX(), game_->getGraphics().getSprite(2)->getPosY());
		platforms[1].Move(game_->getGraphics().getSprite(3)->getPosX(), game_->getGraphics().getSprite(3)->getPosY());

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
	game_->getGraphics().loadTexture("Data/BG.tga", false); //BG
	game_->getGraphics().loadTexture("Data/PlayerTest.tga"); //Player
	game_->getGraphics().getSprite(1)->setEntity();
	game_->getGraphics().getSprite(1)->getPosX() = 85;
	game_->getGraphics().getSprite(1)->getPosY() = 359;
	playerRect = Rectangle(game_->getGraphics().getSprite(1)->getWidth(), game_->getGraphics().getSprite(1)->getHeight());
	game_->getGraphics().loadTexture("Data/test.tga", false); //Ground
	game_->getGraphics().getSprite(2)->setEntity();
	game_->getGraphics().getSprite(2)->getPosY() = 400;
	platformRect = Rectangle(game_->getGraphics().getSprite(2)->getWidth(), game_->getGraphics().getSprite(2)->getHeight());
	platforms.push_back(platformRect);
	game_->getGraphics().loadTexture("Data/platform1.tga", false); //Platform 1
	game_->getGraphics().getSprite(3)->setEntity();
	game_->getGraphics().getSprite(3)->getPosY() = 300;
	game_->getGraphics().getSprite(3)->getPosX() = 300;
	Rectangle platform2Rect = Rectangle(game_->getGraphics().getSprite(3)->getWidth(), game_->getGraphics().getSprite(3)->getHeight());
	platforms.push_back(platform2Rect);

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
				game_->getGraphics().getSprite(1)->getPosY() -= 1;
			}
			else
				game_->getGraphics().getSprite(1)->getPosY() += 1;
		}
		else
		{
			game_->getGraphics().getSprite(1)->getPosY() -= 1;
			if (col)
			{
				jumping_time = gameClock - 1;
			}
		}
			
	}
}


