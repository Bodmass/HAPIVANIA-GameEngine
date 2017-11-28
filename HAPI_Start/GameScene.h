#pragma once 

#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"
#include "GameObject.h"

using namespace HAPISPACE;

class Game;
class GameScene
{
private:

	std::vector<Rectangle> platforms;
	std::vector<GameObject*> gameObjects;

	GameObject* BG;
	GameObject* player;
	GameObject* platform1;
	GameObject* platform2;


	//Player Info
	int playerSpeed = 1;
	bool player_isJumping{ false };
	int jumping_time = 0;
	int jumptime2 = 0;

	int gameClock;
	void player_Jump();

	Game* game_ = nullptr;

	bool col = false;

public:

	void update();
	void loadTextures();
	void loadGameObject();
	GameScene(Game* game);
	~GameScene();
};

