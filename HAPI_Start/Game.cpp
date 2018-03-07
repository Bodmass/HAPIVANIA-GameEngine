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
		boss = BossScene(this);
		title = TitleScreen(this);
		pause = PauseMenu(this);
		gameover = GameOverScene(this);
		end = EndScene(this);
		current = &title;


		HAPI.SetShowFPS(true);
		HAPI.SetIcon(Icon, 32, 32);
		Update();
	}
}

void Game::Update()
{
	end.loadTextures();
	end.loadGameObject();
	//Setup Title
	title.loadTextures();
	title.loadGameObject();
	title.loadSounds();
	//Setup Level
	game.loadTextures();
	game.loadGameObject();
	game.loadSounds();
	game.loadLevel("Data/DemoLevel.xml");
	//Setup GameOver
	gameover.loadTextures();
	gameover.loadSounds();
	//Setup Pause Menu
	pause.loadTextures();
	pause.loadGameObject();
	//Setup Boss Level
	boss.loadTextures();
	boss.loadGameObject();
	boss.loadSounds();
	boss.loadLevel("Data/DemoLevel2.xml");


	double time = 0;
	double deltaTime = 0;
	double timesincelasttick = 0;
	double timebetweenticks = 1000 / 60;
	double timebetweenlock = 3000 / 60;
	while (HAPI.Update())
	{
		deltaTime = HAPI.GetTime() - time;
		time = HAPI.GetTime();
		if (CheckReset())
		{
			game = GameScene(this);
			game.loadGameObject();
			game.loadLevel("Data/DemoLevel.xml");
			SetReset(false);
		}
		while(timesincelasttick > timebetweenticks) //lock refresh rate
		{

			timesincelasttick -= timebetweenticks;
			const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);
			current->update();

		}



		
		current->render();
		timesincelasttick += deltaTime;

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

