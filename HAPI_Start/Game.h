
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
	bool isRunning{ true }; //Game Loop
		int screenWidth{ 1280 }, screenHeight{ 720 };
	int CamX{ 0 }, CamY{ 0 }; //Camera Position
	int posX{ 1 }, posY{ 1 };
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData(); //Keyboard Access
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0); //Controller Access
	Visualisation graphics;
	BYTE* screen = nullptr; 
	Rectangle screenRect;
	Scene* current = nullptr; //Scene that is always played and just swaps what it's pointing to.
	GameScene game = nullptr; //Stage 1 Scene
	BossScene boss = nullptr; //Stage 2 Scene
	TitleScreen title = nullptr; //Title Scene
	PauseMenu pause = nullptr; //Pause Scene
	GameOverScene gameover = nullptr; //Death Scene
	EndScene end = nullptr; //Credits
	bool pauseLock = false;
	std::string room; //Contains name of the Scene
	std::string difficulty = "Easy"; //Easy, Hard Modes

	Texture icontexture = "Textures/Icon.png"; //Game Icon
	BYTE* Icon = icontexture.getSprite();

	//Global Booleans for Player Upgrades
	bool p_SprintU = false;
	bool p_SuperJump = false;
	bool p_XRAYB = false;
	bool hasReset = false;
	bool GameScene_TilesLoaded = false;
	
public:
	Game();
	~Game();
	void Run();
	void Update();
	
	
	HAPI_TColour setColour(BYTE* screen, int r, int g, int b, int a);

	int getCameraX() { return CamX; } //Return Camera X
	int getCameraY() { return CamY; } //Return Camera Y
	int getScreenWidth() { return screenWidth; } //Return Screen Width
	int getScreenHeight() { return screenHeight; } //Return Screen Height
	void setCamera(int x, int y) { CamX = x; CamY = y; } //Set the X and Y position of the Camera.
	HAPI_TKeyboardData getKeyboard() { return keyData; } //Get access to the Keyboard
	HAPI_TControllerData getController() { return controllerData; } //Get access to the Controller
	Rectangle& getScreenRect() { return screenRect; } //Returns the Screen Rectangle
	bool checkRunning() { return isRunning; } 
	Visualisation& getGraphics() { return graphics; }
	BYTE* getScreen() { return screen; }

	//-Swap Scenes-//
	void switchScene_Title() { current = &title; }
	void switchScene_Game() { current = &game; }
	void switchScene_Boss() { current = &boss; }
	void switchScene_Pause() { current = &pause; }
	void switchScene_Death() { current = &gameover; }
	void switchScene_End() { current = &end; }
	//--//

	//Reset Level-//
	void SetReset(bool yesno) { hasReset = yesno; }
	bool CheckReset() { return hasReset; }

	//Tiles
	void Set_GameScene_TilesLoaded(bool yesno) { GameScene_TilesLoaded = yesno; }
	bool Check_GameScene_TilesLoaded() { return GameScene_TilesLoaded; }
	//-//

	//Pause Screen-//
	bool getPauseLock() { return pauseLock; }
	void setPauseLock(bool yesno) { pauseLock = yesno; }
	//--//

	void setRoom(std::string level) {room = level;}
	void setPlayer(Player* p) { boss.setPlayer(p); }
	std::string getRoom() { return room; }

	//-Player Upgrades-//
	bool p_SprintU_Get() { return p_SprintU; }
	bool p_SuperJump_Get() { return p_SuperJump; }
	bool p_XRAYB_Get() { return p_XRAYB; }
	void p_XRAYB_Set(bool yesno) { p_XRAYB = yesno; }
	void p_SprintU_Set(bool yesno) { p_SprintU = yesno; }
	void p_SuperJump_Set(bool yesno) { p_SuperJump = yesno; }
	//--//

	//-Difficulties-//
	std::string getDifficulty() { return difficulty; }
	void setHardMode() { difficulty = "Hard"; }
	void setEasyMode() { difficulty = "Easy"; }
	bool isHardMode() { if (difficulty == "Hard") return true; return false; }
	//--//

};
