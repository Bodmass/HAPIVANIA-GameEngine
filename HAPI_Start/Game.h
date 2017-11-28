
#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"
#include "GameScene.h"
#include "TitleScreen.h"

using namespace HAPISPACE;



class Game 
{

private:
	bool isRunning{ true };
	int screenWidth{ 900 }, screenHeight{ 600 };
	int CamX{ 0 }, CamY{ 0 };
	int posX{ 1 }, posY{ 1 };
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	Visualisation graphics;
	BYTE* screen = nullptr;
	Rectangle screenRect;
	GameScene* current = nullptr;
	GameScene game = nullptr;
	TitleScreen title = nullptr;
	



//#define HK_ANALOGUE_LEFT_THUMB_X		2
//#define HK_ANALOGUE_LEFT_THUMB_Y		3
//#define HK_ANALOGUE_RIGHT_THUMB_X		4
//#define HK_ANALOGUE_RIGHT_THUMB_Y		5

public:
	Game();
	~Game();
	void Run();
	void Update();
	
	HAPI_TColour setColour(BYTE* screen, int r, int g, int b, int a);
	int getCameraX() { return CamX; }
	int getCameraY() { return CamY; }
	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
	void setCamera(int x, int y) { CamX = x; CamY = y; }
	HAPI_TKeyboardData getKeyboard() { return keyData; }
	Rectangle& getScreenRect() { return screenRect; }
	bool checkRunning() { return isRunning; }
	Visualisation& getGraphics() { return graphics; }
	BYTE* getScreen() { return screen; }

	void switchScene_Title() { current = &title; }
	void switchScene_Game() { current = &game; }


};
