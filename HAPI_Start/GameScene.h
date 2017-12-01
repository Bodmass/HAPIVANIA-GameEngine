#pragma once 

#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "SpriteAnimator.h"

using namespace HAPISPACE;

class Game;
class GameScene
{
private:

	std::vector<Rectangle> platforms;
	std::vector<GameObject*> gameObjects;

	Texture* playerSprite = nullptr;

	//Animations
	Texture* playerSprites_LeftIdle = nullptr;
	Texture* playerSprites_RightIdle = nullptr;
	SpriteAnimator* playerSprites_LeftRun = nullptr;
	SpriteAnimator* playerSprites_RightRun = nullptr;
	SpriteAnimator* playerSprites_LeftSprint = nullptr;
	SpriteAnimator* playerSprites_RightSprint = nullptr;
	SpriteAnimator* playerSprites_LeftJump = nullptr;
	SpriteAnimator* playerSprites_RightJump = nullptr;
	Texture* playerSprites_RightFall = nullptr;
	Texture* playerSprites_LeftFall = nullptr;


	int leftRunStartIndex = -1;
	int rightRunStartIndex = -1;
	int leftSprintStartIndex = -1;
	int rightSprintStartIndex = -1;
	int leftJumpStartIndex = -1;
	int rightJumpStartIndex = -1;


	GameObject* BG;
	GameObject* player;
	GameObject* platform1;
	GameObject* platform2;

	Rectangle playerRect = Rectangle(48, 48);

	//Player Info
	int playerSpeed = 1;
	int jumpspeed = 3;
	bool player_isJumping{ false };
	bool player_isFalling{ false };
	int jumping_time = 0;
	int jumptime2 = 0;

	int gameClock;
	void player_Jump();

	bool playerGrounded = true;
	bool playerSprint = false;
	bool isLeft = false;
	bool isRight = false;
	bool col = false;
	bool BGMPlaying = false;

protected:
	Game* game_ = nullptr;
public:

	virtual void update();
	virtual void render();
	virtual void loadTextures();
	virtual void loadGameObject();
	GameScene(Game* game);
	virtual~GameScene();
	Game* getGame() { return game_; }
};

