
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
#include "GameOverScene.h"
#include "BossScene.h"
#include "EndScene.h"
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
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);
	Visualisation graphics;
	BYTE* screen = nullptr;
	Rectangle screenRect;
	Scene* current = nullptr;
	GameScene game = nullptr;
	BossScene boss = nullptr;
	TitleScreen title = nullptr;
	PauseMenu pause = nullptr;
	GameOverScene gameover = nullptr;
	EndScene end = nullptr;
	bool pauseLock = false;
	std::string room;
	std::string difficulty = "Easy"; //Easy, Hard

	Texture icontexture = "Textures/Icon.png";
	BYTE* Icon = icontexture.getSprite();

	bool p_SprintU = false;
	bool p_SuperJump = false;
	bool p_XRAYB = false;
	



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
	HAPI_TControllerData getController() { return controllerData; }
	Rectangle& getScreenRect() { return screenRect; }
	bool checkRunning() { return isRunning; }
	Visualisation& getGraphics() { return graphics; }
	BYTE* getScreen() { return screen; }

	void switchScene_Title() { current = &title; }
	void switchScene_Game() { current = &game; }
	void switchScene_Boss() { current = &boss; }
	void switchScene_Pause() { current = &pause; }
	void switchScene_Death() { current = &gameover; }
	void switchScene_End() { current = &end; }
	bool getPauseLock() { return pauseLock; }
	void setPauseLock(bool yesno) { pauseLock = yesno; }
	void setRoom(std::string level) {room = level;}
	void setPlayer(Player* p) { boss.setPlayer(p); }
	std::string getRoom() { return room; }

	bool p_SprintU_Get() { return p_SprintU; }
	bool p_SuperJump_Get() { return p_SuperJump; }
	bool p_XRAYB_Get() { return p_XRAYB; }
	void p_XRAYB_Set(bool yesno) { p_XRAYB = yesno; }
	void p_SprintU_Set(bool yesno) { p_SprintU = yesno; }
	void p_SuperJump_Set(bool yesno) { p_SuperJump = yesno; }
	std::string getDifficulty() { return difficulty; }
	void setHardMode() { difficulty = "Hard"; }
	void setEasyMode() { difficulty = "Easy"; }


};
