#pragma once
#include "Scene.h"
#include "Player.h"
#include "Pickup.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"

class BossScene :
	public Scene
{
private:

	std::vector<Enemy*> enemies;
	std::vector<Rectangle> platforms;
	std::vector<Pickup*> pickups;
	std::vector<GameObject*> gameObjects;
	std::vector<Bullet*> bulletObjects;
	std::vector<Bullet*> bossBullets;
	std::vector<GameObject*> gameUI;

	GameObject* HUDBar;

	Texture* playerSprite = nullptr;
	//Animations
	Texture* playerSprites_LeftIdle = nullptr;
	Texture* playerSprites_RightIdle = nullptr;
	Texture* playerSprites_LeftUpIdle = nullptr;
	Texture* playerSprites_RightUpIdle = nullptr;
	SpriteAnimator* playerSprites_LeftRun = nullptr;
	SpriteAnimator* playerSprites_RightRun = nullptr;
	//
	SpriteAnimator* playerSprites_LeftUpRun = nullptr;
	SpriteAnimator* playerSprites_RightUpRun = nullptr;
	//
	SpriteAnimator* playerSprites_LeftSprint = nullptr;
	SpriteAnimator* playerSprites_RightSprint = nullptr;
	SpriteAnimator* playerSprites_LeftJump = nullptr;
	SpriteAnimator* playerSprites_RightJump = nullptr;
	Texture* playerSprites_RightFall = nullptr;
	Texture* playerSprites_LeftFall = nullptr;

	//Enemy

	SpriteAnimator* ship_Idle = nullptr;
	GameObject* doorDestroy = nullptr;
	bool doorDestroyed = false;


	SpriteAnimator* spacePirate_LeftRun = nullptr;
	SpriteAnimator* spacePirate_RightRun = nullptr;

	SpriteAnimator* bat_LeftRun = nullptr;
	SpriteAnimator* bat_RightRun = nullptr;

	Boss* Ship = nullptr;


	int leftRunStartIndex = -1;
	int rightRunStartIndex = -1;
	int leftSprintStartIndex = -1;
	int rightSprintStartIndex = -1;
	int leftJumpStartIndex = -1;
	int rightJumpStartIndex = -1;


	GameObject* BG;
	Player* player;
	Pickup* Sprint_PU;

	Rectangle* CamRect = nullptr;

	Rectangle playerRect = Rectangle(48, 48);

	int gameClock;
	int GameStartWait;
	int GameEndWait;
	bool Setup = false;
	bool BGMPlaying = false;
	bool GameStarted = false;
	bool CameraLocked = false;
	bool musicstopped = false;
	bool BossActivated = false;
	bool BossFight_Phase1 = false;

public:
	
	void StartBoss();


	void setPlayer(Player* p) { player = p; }
	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
	virtual void loadSounds() override;
	void loadLevel(std::string level);
	BossScene(Game* game) : Scene(game) {};
	~BossScene();
	//virtual Game* getGame() { return game_; }
};

