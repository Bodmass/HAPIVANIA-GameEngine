#include "Game.h"

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


		setColour(screen, 0, 0, 0, 255); //Clear screen to colour
		for (size_t i = 0; i < graphics.getSpriteMap().size(); i++)
		{
			//if (graphics.getSprite(i)->getAlpha())
			if(graphics.getSprite(i)->getAlpha())
				graphics.BlitAlpha(screen, screenRect, graphics.getSprite(i), getCameraX(), getCameraY());
			else
				graphics.Blit(screen, screenRect, graphics.getSprite(i), getCameraX(), getCameraY());
		}

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

		if (keyData.scanCode[HK_DOWN])
			graphics.getSprite(1)->getPosY() += 1;
		if (keyData.scanCode[HK_UP])
			graphics.getSprite(1)->getPosY() -= 1;
		if (keyData.scanCode[HK_LEFT])
			graphics.getSprite(1)->getPosX() -= 1;
		if (keyData.scanCode[HK_RIGHT])
			graphics.getSprite(1)->getPosX() += 1;

		if (keyData.scanCode['S'])
			CamY += 1;
		if (keyData.scanCode['W'])
			CamY -= 1;
		if (keyData.scanCode['A'])
			CamX -= 1;
		if (keyData.scanCode['D'])
			CamX += 1;

	}
	delete[] screenRect;
	//delete[] playerRect;
	isRunning = false;
}

void Game::loadTextures()
{
	graphics.loadTexture("Data/BG.tga", false); //BG
	graphics.loadTexture("Data/PlayerTest.tga"); //Player
	graphics.getSprite(1)->setEntity();
	graphics.loadTexture("Data/test.tga", false); //BG2
	graphics.getSprite(2)->setEntity();
	graphics.getSprite(2)->getPosY() = 400;
	//playerRect = new Rectangle(graphics.getSprite(1)->getWidth(), graphics.getSprite(1)->getHeight());

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

