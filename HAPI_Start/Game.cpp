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
		screenRect = Rectangle(screenWidth, screenHeight);
		game = GameScene(this);
		title = TitleScreen(this);
		current = &title;

		HAPI.SetShowFPS(true);
		
		Update();
	}
}

void Game::Update()
{
	game.loadTextures();
	game.loadGameObject();
	title.loadTextures();
	title.loadGameObject();
	while (HAPI.Update())
	{
		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);
		current->update();
	}
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

