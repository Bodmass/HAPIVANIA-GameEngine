#pragma once 

#include "Scene.h"
#include "Player.h"

class GameScene : public Scene
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
	Player* player;
	GameObject* platform1;
	GameObject* platform2;

	Rectangle playerRect = Rectangle(48, 48);

	int gameClock;
	bool BGMPlaying = false;

public:

	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
	GameScene(Game* game) : Scene(game) {};
	~GameScene();
	//virtual Game* getGame() { return game_; }
};

