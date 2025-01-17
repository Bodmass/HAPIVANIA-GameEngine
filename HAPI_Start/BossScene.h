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

	//ALL ENTITY VECTORS
	std::vector<Enemy*> enemies;
	std::vector<Rectangle> platforms;
	std::vector<Pickup*> pickups;
	std::vector<GameObject*> gameObjects;
	std::vector<Bullet*> bulletObjects;
	std::vector<Bullet*> bossBullets;


	//UI
	std::vector<GameObject*> gameUI;
	GameObject* HUDBar;


	//////////////////////////////////////////////////////////
	//Player Textures
	Texture* playerSprite = nullptr;
	Texture* playerSprites_LeftIdle = nullptr;
	Texture* playerSprites_RightIdle = nullptr;
	Texture* playerSprites_LeftUpIdle = nullptr;
	Texture* playerSprites_RightUpIdle = nullptr;
	Texture* playerSprites_RightFall = nullptr;
	Texture* playerSprites_LeftFall = nullptr;
	//Player Animations
	SpriteAnimator* playerSprites_LeftRun = nullptr;
	SpriteAnimator* playerSprites_RightRun = nullptr;
	SpriteAnimator* playerSprites_LeftUpRun = nullptr;
	SpriteAnimator* playerSprites_RightUpRun = nullptr;
	SpriteAnimator* playerSprites_LeftSprint = nullptr;
	SpriteAnimator* playerSprites_RightSprint = nullptr;
	SpriteAnimator* playerSprites_LeftJump = nullptr;
	SpriteAnimator* playerSprites_RightJump = nullptr;
	//Misc
	int leftRunStartIndex = -1;
	int rightRunStartIndex = -1;
	int leftSprintStartIndex = -1;
	int rightSprintStartIndex = -1;
	int leftJumpStartIndex = -1;
	int rightJumpStartIndex = -1;
	//////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////
	//Enemies Animation

	SpriteAnimator* ship_Idle = nullptr;
	GameObject* doorDestroy = nullptr;



	SpriteAnimator* spacePirate_LeftRun = nullptr;
	SpriteAnimator* spacePirate_RightRun = nullptr;

	SpriteAnimator* bat_LeftRun = nullptr;
	SpriteAnimator* bat_RightRun = nullptr;


	//////////////////////////////////////////////////////////

	bool doorDestroyed = false;



	//////////////////////////////////////////////////////////
	//Entities
	GameObject* BG;
	Player* player;
	Pickup* Sprint_PU;
	Boss* Ship = nullptr;
	//////////////////////////////////////////////////////////

	Rectangle* CamRect = nullptr;

	Rectangle playerRect = Rectangle(48, 48);

	int gameClock;
	int GameStartWait;
	int GameEndWait;

	//Game Switches
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
};

