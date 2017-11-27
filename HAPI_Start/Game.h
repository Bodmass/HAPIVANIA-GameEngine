#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"

using namespace HAPISPACE;

#pragma once
class Game
{

private:
	bool isRunning{ true };
	int screenWidth{ 900 }, screenHeight{ 600 };
	int posX{ 1 }, posY{ 1 };
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	Visualisation graphics;
	BYTE* screen;
	Rectangle* screenRect;
	Rectangle* playerRect;
	Rectangle* platformRect;
	int CamX{ 0 }, CamY{ 0 };

	//Player Info
	int playerSpeed = 1;
	bool player_isJumping{ false };
	int jumping_time = 0;
	int jumptime2 = 0;


//#define HK_ANALOGUE_LEFT_THUMB_X		2
//#define HK_ANALOGUE_LEFT_THUMB_Y		3
//#define HK_ANALOGUE_RIGHT_THUMB_X		4
//#define HK_ANALOGUE_RIGHT_THUMB_Y		5

public:
	Game();
	~Game();
	void Run();
	void Update();
	void loadTextures();
	HAPI_TColour setColour(BYTE* screen, int r, int g, int b, int a);
	int getCameraX() { return CamX; }
	int getCameraY() { return CamY; }
	int gameClock;
	void player_Jump();

};

