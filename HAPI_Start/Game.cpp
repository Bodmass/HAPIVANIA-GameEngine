#include "Game.h"
#include "CollisionDetection.h"

Game::Game()
{
	if (!HAPI.Initialise(screenWidth, screenHeight, "GEC HAPIvania Engine - Aziz Arar s6053935"))
		return;
	
}


Game::~Game()
{
}

void Game::Run()
{
	if (isRunning)
	{
		screen = HAPI.GetScreenPointer();
		screenRect = new Rectangle(screenWidth, screenHeight);
		HAPI.SetShowFPS(true);
		loadTextures();
		Update();
	}
}

void Game::Update()
{
	while (HAPI.Update())
	{
		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

		gameClock = HAPI.GetTime();

		setColour(screen, 0, 0, 0, 255); //Clear screen to colour
		for (size_t i = 0; i < graphics.getSpriteMap().size(); i++)
		{
			//if (graphics.getSprite(i)->getAlpha())
			if (graphics.getSprite(i)->getAlpha())
				graphics.BlitAlpha(screen, screenRect, graphics.getSprite(i), getCameraX(), getCameraY());
			else
				graphics.Blit(screen, screenRect, graphics.getSprite(i), getCameraX(), getCameraY());
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



		if (keyData.scanCode[HK_LSHIFT])
			playerSpeed = 2;
		else
			playerSpeed = 1;

		Rectangle* player2;
		player2 = new Rectangle(graphics.getSprite(1)->getWidth(), graphics.getSprite(1)->getHeight());
		player2->Move(graphics.getSprite(1)->getPosX() + 1, graphics.getSprite(1)->getPosY() + 1);

		if (!CollisionDetection::CheckCollision(*player2, *platformRect) && !player_isJumping)
		{
			graphics.getSprite(1)->getPosY() += playerSpeed;
		}

		/*
		if (keyData.scanCode['S'])
		{
			if (!CollisionDetection::CheckCollision(*player2, *platformRect))
			{
				graphics.getSprite(1)->getPosY() += playerSpeed;
			}
			if (CollisionDetection::CheckCollision(*player2, *platformRect))
				graphics.getSprite(1)->getPosY() -= playerSpeed * 2;
		}

		
		if (keyData.scanCode['W'])
		{
			if (!CollisionDetection::CheckYCollision(*playerRect, *platformRect))
			{
				graphics.getSprite(1)->getPosY() -= playerSpeed;
			}
		}

		*/
		if (keyData.scanCode['A'])
		{
			if (!CollisionDetection::CheckCollision(*playerRect, *platformRect))
			{
				graphics.getSprite(1)->getPosX() -= playerSpeed;
				if (graphics.getSprite(1)->getPosX() > screenWidth / 2)
					CamX += playerSpeed;
				else
					CamX = 0;
			}

		}

		if (keyData.scanCode['D'])
		{
			if (!CollisionDetection::CheckCollision(*playerRect, *platformRect))
			{
				graphics.getSprite(1)->getPosX() += playerSpeed;
				if (graphics.getSprite(1)->getPosX() > screenWidth / 2)
					CamX -= playerSpeed;
				else
					CamX = 0;
			}
		}//85,359

		if (keyData.scanCode['W'] || keyData.scanCode[HK_SPACE])
		{
			if (!player_isJumping)
				player_Jump();

		}
		if (player_isJumping)
			player_Jump();

		delete[] player2;

		playerRect->Move(graphics.getSprite(1)->getPosX(), graphics.getSprite(1)->getPosY());
		platformRect->Move(graphics.getSprite(2)->getPosX(), graphics.getSprite(2)->getPosY());

		if (keyData.scanCode[HK_DOWN])
			CamY += playerSpeed;
		if (keyData.scanCode[HK_UP])
			CamY -= playerSpeed;
		if (keyData.scanCode[HK_LEFT])
			CamX -= playerSpeed;
		if (keyData.scanCode[HK_RIGHT])
			CamX += playerSpeed;

	}
	delete[] screenRect;
	delete[] playerRect;
	delete[] platformRect;
	isRunning = false;
}

void Game::loadTextures()
{
	graphics.loadTexture("Data/BG.tga", false); //BG
	graphics.loadTexture("Data/PlayerTest.tga"); //Player
	graphics.getSprite(1)->setEntity();
	graphics.getSprite(1)->getPosX() = 85;
	graphics.getSprite(1)->getPosY() = 359;
	playerRect = new Rectangle(graphics.getSprite(1)->getWidth(), graphics.getSprite(1)->getHeight());
	graphics.loadTexture("Data/test.tga", false); //BG2
	graphics.getSprite(2)->setEntity();
	graphics.getSprite(2)->getPosY() = 400;
	platformRect = new Rectangle(graphics.getSprite(2)->getWidth(), graphics.getSprite(2)->getHeight());


}



HAPI_TColour Game::setColour(BYTE* screen, int r, int g, int b, int a)
{
	HAPI_TColour col{ HAPI_TColour(r,g,b) };

	for (int i = 0; i < screenWidth*screenHeight; i++)
	{
		screen[i * 4] = col.red;
		screen[i * 4 + 1] = col.green;
		screen[i * 4 + 2] = col.blue;
		screen[i * 4 + 3] = col.alpha;
	}

	return col;
}

void Game::player_Jump()
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
			if (CollisionDetection::CheckCollision(*playerRect, *platformRect))
			{
				graphics.getSprite(1)->getPosY() -= 1;
				player_isJumping = false;
			}
			else
				graphics.getSprite(1)->getPosY() += 1;
		}
		else
			graphics.getSprite(1)->getPosY() -= 1;
	}
}

