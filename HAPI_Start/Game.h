
#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"
#include "Scene.h"
#include "GameScene.h"
#include "TitleScreen.h"
#include "PauseMenu.h"
#include "Sound.h"

using namespace HAPISPACE;



class Game 
{

private:
	bool isRunning{ true };
	int screenWidth{ 1280 }, screenHeight{ 720 };
	int CamX{ 0 }, CamY{ 0 };
	int posX{ 1 }, posY{ 1 };
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	Visualisation graphics;
	Sound audio;
	BYTE* screen = nullptr;
	Rectangle screenRect;
	Scene* current = nullptr;
	GameScene game = nullptr;
	TitleScreen title = nullptr;
	PauseMenu pause = nullptr;
	bool pauseLock = false;

	Texture icontexture = "Textures/Icon.png";
	BYTE* Icon = icontexture.getSprite();

	bool p_SprintU = false;
	bool p_SuperJump = false;
	



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
	Sound& getAudio() { return audio; }
	BYTE* getScreen() { return screen; }

	void switchScene_Title() { current = &title; }
	void switchScene_Game() { current = &game; }
	void switchScene_Pause() { current = &pause; }
	bool getPauseLock() { return pauseLock; }
	void setPauseLock(bool yesno) { pauseLock = yesno; }

	bool p_SprintU_Get() { return p_SprintU; }
	bool p_SuperJump_Get() { return p_SuperJump; }
	void p_SprintU_Set(bool yesno) { p_SprintU = yesno; }
	void p_SuperJump_Set(bool yesno) { p_SuperJump = yesno; }


};
