#include "GameScene.h"
#include "Game.h"
#include "CollisionDetection.h"

GameScene::~GameScene()
{

	delete playerSprites_LeftRun;
	delete playerSprites_RightRun;
	delete playerSprites_LeftSprint;
	delete playerSprites_RightSprint;
	delete playerSprites_LeftJump;
	delete playerSprites_RightJump;

	for (auto* gameObject : gameObjects)
	{
		delete gameObject;
	}

	for (auto* enemy : enemies)
	{
		delete enemy;
	}
}


void GameScene::update()
{
	gameClock = HAPI.GetTime();
	if (!Setup)
	{
		player->PlayerUpdate();
		GameStartWait = gameClock;
		GameStartWait = gameClock + 7000;
		Sound::playMusic("Appear");
		Setup = true;

		for (auto p : pickups)
		{
			p->Update(player);
		}
	}

	if (!BGMPlaying)
	{
		if(gameClock > GameStartWait)
		{
			Sound::playMusic("BGM 1");
			BGMPlaying = true;
			GameStarted = true;
		}
	}

	if (GameStarted)
	{
		Rectangle* CamRect = new Rectangle(game_->getScreenWidth(), game_->getScreenHeight());
		CamRect->Translate(-game_->getCameraX(), -game_->getCameraY());

		player->PlayerCollision(platforms, *CamRect);

		player->PlayerUpdate();

		if (player->PlayerShoot(bulletObjects))
		{
			//Check if the Player Shoots, if they do, move the bullet to the back (so we can rotate between a number of them)
			std::rotate(bulletObjects.begin(), bulletObjects.begin() + 1, bulletObjects.end());
		}

		for (auto b : bulletObjects)
		{
			if (b->checkActive())
			{
				b->Update();

				if (!CamRect->rOutside(b->getRect()))
					b->Destroy();



				if (!player->checkXRAYUpgrade())
				{
					b->CheckCollision(platforms);
				}
				else
				{
					if (b->getTexture() != game_->getGraphics().getSprite("Player_Bullet_2"))
						b->setTexture(game_->getGraphics().getSprite("Player_Bullet_2"));
				}
			}
		}

		for (auto p : pickups)
		{
			if(CamRect->rOutside(p->getRect()))
				p->Update(player);
		}

		for (auto e : enemies)
		{
			e->Update(player);
		}

		if (player->getY() > (game_->getCameraY() + game_->getScreenHeight()))
			player->Attacked(99); //Instant Death

		if (!player->p_CheckAlive())
		{
			Sound::stopMusic("BGM 1");
			game_->switchScene_Death();
		}

		delete CamRect;
	}



		//SET CAMERA

		int distancefromcameraX = abs((player->getX() + 48) - (game_->getScreenWidth() / 2));
		int distancefromcameraY = abs(player->getY() - (game_->getScreenHeight() / 2));
		
		if (player->getX() + 48 > (game_->getScreenWidth() / 2))
		{
			game_->setCamera(-distancefromcameraX, game_->getCameraY());
		}
		else
			game_->setCamera(0, game_->getCameraY());

		if (player->getY() < (game_->getScreenHeight() / 2))
		{
			game_->setCamera(game_->getCameraX(), distancefromcameraY);
		}

		//END CAMERA

		
		if (player && platforms.size() >= 2)
		{
			player->getRect().Move(player->getX(), player->getY());
			//Sprint_PU->getRect().Move(Sprint_PU->getX(), Sprint_PU->getY());
		}
		


		if (game_->getKeyboard().scanCode[HK_ESCAPE] && !game_->getPauseLock())
		{
			game_->setPauseLock(true);
			game_->switchScene_Pause();
			//TEMP HERE
			game_->p_SprintU_Set(player->checkSprintUpgrade());
			game_->p_XRAYB_Set(player->checkXRAYUpgrade());
			game_->p_SuperJump_Set(player->checkJumpUpgrade());
		}

		if (!game_->getKeyboard().scanCode[HK_ESCAPE])
		{
			game_->setPauseLock(false);
		}

}

void GameScene::render()
{
	for (auto* gameObject : gameObjects)
	{

		if (gameObject->getTexture()->getAlpha())
			game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), gameObject->getTexture(), gameObject->getX(), gameObject->getY(), game_->getCameraX(), game_->getCameraY());
		else
			game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), gameObject->getTexture(), gameObject->getX(), gameObject->getY(), game_->getCameraX(), game_->getCameraY());
	}

	for (auto* enemy : enemies)
	{
		game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), enemy->getTexture(), enemy->getX(), enemy->getY(), game_->getCameraX(), game_->getCameraY());
	}

	HAPI.RenderText(10, 10, HAPI_TColour::WHITE, std::to_string(player->p_getcurHP()), 34);
}

void GameScene::loadTextures()
{
	game_->getGraphics().loadTexture("Background","Textures/Level/BGs/BG1.tga", false); //0 - BG -
	game_->getGraphics().loadTexture("HUDBar", "Textures/UI/HUD/HUDBar.png", false); //HUD Bar
	//BULLETS
	game_->getGraphics().loadTexture("Player_Bullet_1", "Textures/Player/Bullets/BasicBullet.png"); //58
	game_->getGraphics().loadTexture("Player_Bullet_2", "Textures/Player/Bullets/XRAYBullet.png"); //58

	//PICKUPS
	game_->getGraphics().loadTexture("Pickup_Sprint_1", "Textures/Pickups/Sprint/Sprint_0.png"); //58
	game_->getGraphics().loadTexture("Pickup_XRAY_1", "Textures/Pickups/Xray/XRAY_0.png"); //58

	//ENEMIES
	game_->getGraphics().loadTexture("Enemy_SP_FaceLeft", "Textures/AI/SpacePirate/SpacePirate_10.png");
	game_->getGraphics().loadTexture("Enemy_SP_FaceRight", "Textures/AI/SpacePirate/SpacePirate_02.png");

	//PLAYER//
	//IDLE
	game_->getGraphics().loadTexture("Player_Idle","Textures/Player/Player_01.png"); //3 - Player - 
	//LEFT IDLE
	game_->getGraphics().loadTexture("Player_Left_Idle", "Textures/Player/Player_12.png"); //4
	//LEFT RUN
	leftRunStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Left_Run_1", "Textures/Player/Player_13.png"); //5
	game_->getGraphics().loadTexture("Player_Left_Run_2", "Textures/Player/Player_14.png"); //6
	game_->getGraphics().loadTexture("Player_Left_Run_3", "Textures/Player/Player_15.png"); //7
	game_->getGraphics().loadTexture("Player_Left_Run_4", "Textures/Player/Player_16.png"); //8
	game_->getGraphics().loadTexture("Player_Left_Run_5", "Textures/Player/Player_17.png"); //9
	game_->getGraphics().loadTexture("Player_Left_Run_6", "Textures/Player/Player_18.png"); //10
	game_->getGraphics().loadTexture("Player_Left_Run_7", "Textures/Player/Player_19.png"); //11
	game_->getGraphics().loadTexture("Player_Left_Run_8", "Textures/Player/Player_20.png"); //12
	game_->getGraphics().loadTexture("Player_Left_Run_9", "Textures/Player/Player_21.png"); //13
	game_->getGraphics().loadTexture("Player_Left_Run_10", "Textures/Player/Player_22.png"); //14
	//RIGHT IDLE
	game_->getGraphics().loadTexture("Player_Right_Idle", "Textures/Player/Player_23.png"); //15
	//RIGHT RUN
	rightRunStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Right_Run_1", "Textures/Player/Player_24.png"); //16
	game_->getGraphics().loadTexture("Player_Right_Run_2", "Textures/Player/Player_25.png"); //17
	game_->getGraphics().loadTexture("Player_Right_Run_3", "Textures/Player/Player_26.png"); //18
	game_->getGraphics().loadTexture("Player_Right_Run_4", "Textures/Player/Player_27.png"); //19
	game_->getGraphics().loadTexture("Player_Right_Run_5", "Textures/Player/Player_28.png"); //20
	game_->getGraphics().loadTexture("Player_Right_Run_6", "Textures/Player/Player_29.png"); //21
	game_->getGraphics().loadTexture("Player_Right_Run_7", "Textures/Player/Player_30.png"); //22
	game_->getGraphics().loadTexture("Player_Right_Run_8", "Textures/Player/Player_31.png"); //23
	game_->getGraphics().loadTexture("Player_Right_Run_9", "Textures/Player/Player_32.png"); //24
	game_->getGraphics().loadTexture("Player_Right_Run_10", "Textures/Player/Player_33.png"); //25
	//LEFT SPRINT
	leftSprintStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Left_Sprint_1", "Textures/Player/Player_34.png"); //26
	game_->getGraphics().loadTexture("Player_Left_Sprint_2", "Textures/Player/Player_35.png"); //27
	game_->getGraphics().loadTexture("Player_Left_Sprint_3", "Textures/Player/Player_36.png"); //28
	game_->getGraphics().loadTexture("Player_Left_Sprint_4", "Textures/Player/Player_37.png"); //29
	game_->getGraphics().loadTexture("Player_Left_Sprint_5", "Textures/Player/Player_38.png"); //30
	game_->getGraphics().loadTexture("Player_Left_Sprint_6", "Textures/Player/Player_39.png"); //31
	game_->getGraphics().loadTexture("Player_Left_Sprint_7", "Textures/Player/Player_40.png"); //32
	game_->getGraphics().loadTexture("Player_Left_Sprint_8", "Textures/Player/Player_41.png"); //33
	game_->getGraphics().loadTexture("Player_Left_Sprint_9", "Textures/Player/Player_42.png"); //34
	game_->getGraphics().loadTexture("Player_Left_Sprint_10", "Textures/Player/Player_43.png"); //35
	//RIGHT SPRINT
	rightSprintStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Right_Sprint_1", "Textures/Player/Player_45.png"); //36
	game_->getGraphics().loadTexture("Player_Right_Sprint_2", "Textures/Player/Player_46.png"); //37
	game_->getGraphics().loadTexture("Player_Right_Sprint_3", "Textures/Player/Player_47.png"); //38
	game_->getGraphics().loadTexture("Player_Right_Sprint_4", "Textures/Player/Player_48.png"); //39
	game_->getGraphics().loadTexture("Player_Right_Sprint_5", "Textures/Player/Player_49.png"); //40
	game_->getGraphics().loadTexture("Player_Right_Sprint_6", "Textures/Player/Player_50.png"); //41
	game_->getGraphics().loadTexture("Player_Right_Sprint_7", "Textures/Player/Player_51.png"); //42
	game_->getGraphics().loadTexture("Player_Right_Sprint_8", "Textures/Player/Player_52.png"); //43
	game_->getGraphics().loadTexture("Player_Right_Sprint_9", "Textures/Player/Player_53.png"); //44
	game_->getGraphics().loadTexture("Player_Right_Sprint_10", "Textures/Player/Player_54.png"); //45
	//LEFT JUMP
	leftJumpStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Left_Jump_1", "Textures/Player/Player_61.png"); //46
	game_->getGraphics().loadTexture("Player_Left_Jump_2", "Textures/Player/Player_62.png"); //47
	game_->getGraphics().loadTexture("Player_Left_Jump_3", "Textures/Player/Player_63.png"); //48
	game_->getGraphics().loadTexture("Player_Left_Jump_4", "Textures/Player/Player_64.png"); //49
	game_->getGraphics().loadTexture("Player_Left_Fall_1", "Textures/Player/Player_65.png"); //50
	game_->getGraphics().loadTexture("Player_Left_Fall_2", "Textures/Player/Player_66.png"); //51
	//RIGHT JUMP
	rightJumpStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Right_Jump_1", "Textures/Player/Player_73.png"); //52
	game_->getGraphics().loadTexture("Player_Right_Jump_2", "Textures/Player/Player_74.png"); //53
	game_->getGraphics().loadTexture("Player_Right_Jump_3", "Textures/Player/Player_75.png"); //54
	game_->getGraphics().loadTexture("Player_Right_Jump_4", "Textures/Player/Player_76.png"); //55
	game_->getGraphics().loadTexture("Player_Right_Fall_1", "Textures/Player/Player_77.png"); //56
	game_->getGraphics().loadTexture("Player_Right_Fall_2", "Textures/Player/Player_78.png"); //57
	
	//END OF PLAYER//
	
	playerSprites_LeftRun = new SpriteAnimator();
	playerSprites_RightRun = new SpriteAnimator();
	playerSprites_LeftSprint = new SpriteAnimator();
	playerSprites_RightSprint = new SpriteAnimator();
	playerSprites_LeftJump = new SpriteAnimator();
	playerSprites_RightJump = new SpriteAnimator();

	//TEMP (Push sprites through a spritesheet instead and fix this?)

	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_1"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_2"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_3"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_4"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_5"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_6"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_7"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_8"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_9"));
	playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite("Player_Left_Run_10"));
	playerSprites_LeftRun->play();

	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_1"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_2"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_3"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_4"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_5"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_6"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_7"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_8"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_9"));
	playerSprites_RightRun->addFrame(game_->getGraphics().getSprite("Player_Right_Run_10"));
	playerSprites_RightRun->play();

	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_1"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_2"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_3"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_4"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_5"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_6"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_7"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_8"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_9"));
	playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite("Player_Right_Sprint_10"));
	playerSprites_RightSprint->play();

	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_1"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_2"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_3"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_4"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_5"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_6"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_7"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_8"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_9"));
	playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite("Player_Left_Sprint_10"));
	playerSprites_LeftSprint->play();

	playerSprites_RightJump->addFrame(game_->getGraphics().getSprite("Player_Right_Jump_3"));
	playerSprites_LeftJump->addFrame(game_->getGraphics().getSprite("Player_Left_Jump_3"));

	//playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite(3));
	/*
	for (int i = 0; i < 10; i++)
	{
		playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite(leftRunStartIndex + i));
	}
	playerSprites_LeftRun->play();

	for (int i = 0; i < 10; i++)
	{
		playerSprites_RightRun->addFrame(game_->getGraphics().getSprite(rightRunStartIndex + i));
	}
	playerSprites_RightRun->play();

	for (int i = 0; i < 10; i++)
	{
		playerSprites_RightSprint->addFrame(game_->getGraphics().getSprite(rightSprintStartIndex + i));
	}
	playerSprites_RightSprint->play();

	for (int i = 0; i < 10; i++)
	{
		playerSprites_LeftSprint->addFrame(game_->getGraphics().getSprite(leftSprintStartIndex + i));
	}
	playerSprites_LeftSprint->play();

	for (int i = 0; i < 4; i++)
	{
		playerSprites_RightJump->addFrame(game_->getGraphics().getSprite(rightJumpStartIndex + i));
	}
	playerSprites_RightJump->play();

	for (int i = 0; i < 4; i++)
	{
		playerSprites_LeftJump->addFrame(game_->getGraphics().getSprite(leftJumpStartIndex + i));
	}
	*/
	//playerSprites_LeftJump->play();

	playerSprites_LeftIdle = game_->getGraphics().getSprite("Player_Left_Idle");
	playerSprites_RightIdle = game_->getGraphics().getSprite("Player_Right_Idle");
	playerSprites_RightIdle->setEntity();
	playerSprites_LeftIdle->setEntity();
	playerSprite = game_->getGraphics().getSprite("Player_Idle");
	playerSprites_LeftFall = game_->getGraphics().getSprite("Player_Left_Fall_2");
	playerSprites_LeftFall->setEntity();
	playerSprites_RightFall = game_->getGraphics().getSprite("Player_Right_Fall_2");
	playerSprites_RightFall->setEntity();

	//END OF PLAYER



	

}

void GameScene::loadGameObject()
{

	BG = new GameObject(game_->getGraphics().getSprite("Background"), Rectangle(game_->getGraphics().getSprite("Background")->getWidth(), game_->getGraphics().getSprite("Background")->getHeight()), 0, 0, true);
	player = new Player(playerSprite, playerRect, 60, 560);
	Sprint_PU = new Pickup(1, game_->getGraphics().getSprite("Pickup_Sprint_1"), Rectangle(game_->getGraphics().getSprite("Pickup_Sprint_1")->getWidth(), game_->getGraphics().getSprite("Pickup_Sprint_1")->getHeight()), 350, 284);
	Pickup* XRAY_PU = new Pickup(3, game_->getGraphics().getSprite("Pickup_XRAY_1"), Rectangle(game_->getGraphics().getSprite("Pickup_XRAY_1")->getWidth(), game_->getGraphics().getSprite("Pickup_XRAY_1")->getHeight()), 2600, 384);
	GameObject* HUDBar = new GameObject(game_->getGraphics().getSprite("HUDBar"), Rectangle(game_->getGraphics().getSprite("HUDBar")->getWidth(), game_->getGraphics().getSprite("HUDBar")->getHeight()), 0, 0, true);


	gameObjects.push_back(BG);
	gameObjects.push_back(player);
	gameObjects.push_back(Sprint_PU);
	gameObjects.push_back(XRAY_PU);
	gameObjects.push_back(HUDBar);

	pickups.push_back(Sprint_PU);
	pickups.push_back(XRAY_PU);

	platforms.push_back(Sprint_PU->getRect());

	player->getRect().Translate(player->getX(), player->getY());
	
	Sprint_PU->getRect().Translate(Sprint_PU->getX(), Sprint_PU->getY());
	XRAY_PU->getRect().Translate(XRAY_PU->getX(), XRAY_PU->getY());

	//Offscreen Bullets
	for (int i = 0; i < 14; i++)
	{
		Bullet* newbullet = new Bullet(game_->getGraphics().getSprite("Player_Bullet_1"), Rectangle(game_->getGraphics().getSprite("Player_Bullet_1")->getWidth(), game_->getGraphics().getSprite("Player_Bullet_1")->getHeight()), -100, -100);
		gameObjects.push_back(newbullet);
		bulletObjects.push_back(newbullet);
	}

	//Enemy (Temp here, move into new function)
	Enemy* SpacePirate = new Enemy(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"), Rectangle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getWidth(), game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getHeight()), 610, 467);
	enemies.push_back(SpacePirate);

	HUDBar->getRect().Translate(HUDBar->getX(), game_->getScreenHeight() - HUDBar->getRect().getHeight());
	//Sprint_PU->setTexture(game_->getGraphics().getSprite(58));
	

	player->set_pSprite(playerSprite);
	player->set_pSprite_LeftIdle(playerSprites_LeftIdle);
	player->set_pSprite_RightIdle(playerSprites_RightIdle);
	player->set_pSprite_LeftFall(playerSprites_LeftFall);
	player->set_pSprite_RightFall(playerSprites_RightFall);
	player->set_pAnim_LeftRun(playerSprites_LeftRun);
	player->set_pAnim_RightRun(playerSprites_RightRun);
	player->set_pAnim_LeftJump(playerSprites_LeftJump);
	player->set_pAnim_RightJump(playerSprites_RightJump);
	player->set_pAnim_LeftSprint(playerSprites_LeftSprint);
	player->set_pAnim_RightSprint(playerSprites_RightSprint);

}

void GameScene::loadSounds()
{
	Sound::addMusic("BGM 1", "Audio/BGM/Stage1.ogg");
	Sound::addMusic("Appear", "Audio/SE/Appear.wav");
	Sound::addSound("Shoot 1", "Audio/SE/laser1.wav");
	Sound::addSound("Shoot 2", "Audio/SE/laser2.wav");
	Sound::addSound("Upgrade", "Audio/SE/ItemRecieved.wav");
	Sound::addSound("Steps", "Audio/SE/steps.wav");
	Sound::addSound("Damaged 1", "Audio/SE/player_damaged1.wav");
	Sound::addSound("Death", "Audio/SE/player_death.wav");
}

void GameScene::loadLevel(std::string level)
{


	CHapiXML levelxml = level;
	//std::cout << "Setting Up Level Sprites: " << level << std::endl;
	std::vector<CHapiXMLNode*> tilesused = levelxml.GetAllNodesWithName("sprite");

	for (auto sprite : tilesused)
	{
		CHapiXMLAttribute attr;
		if (!sprite->GetAttributeWithName("location", attr))
			return; //temp
		std::string tilename = attr.AsString();
		std::string tilelocation = "Textures/Level/Tiles/" + tilename;
		//std::cout << "Sprite Name: " + tilename << " and Location: " + tilelocation << std::endl;
		game_->getGraphics().loadTexture(tilename, tilelocation, false);
	}

	//std::cout << "Setting Up Level Tiles: " << level << std::endl;

	std::vector<CHapiXMLNode*> tilesdown = levelxml.GetAllNodesWithName("tile");

	for (auto t : tilesdown)
	{
		CHapiXMLAttribute attr1;
		if (!t->GetAttributeWithName("x", attr1))
			return; //temp
		//std::cout << attr1.AsString();
		CHapiXMLAttribute attr2;
		if (!t->GetAttributeWithName("y", attr2))
			return; //temp
		//std::cout << ", " << attr2.AsString();
		CHapiXMLAttribute attr3;
		if (!t->GetAttributeWithName("look", attr3))
			return; //temp
		//std::cout << " that looks like " << attr3.AsString() << std::endl;

		bool dontcollide = false;

		if (attr3.AsString() == "Cave/Cave_21.png" || attr3.AsString() == "Cave/Cave_20.png" || attr3.AsString() == "Cave/Cave_18.png" || attr3.AsString() == "Cave/Cave_17.png" || attr3.AsString() == "Cave/Cave_08.png" || attr3.AsString() == "Cave/Cave_09.png" || attr3.AsString() == "Cave/Cave_10.png")
		{
			dontcollide = true;
		}

		std::string t_name = attr3.AsString();


		 
		

		GameObject* newtile = new GameObject(game_->getGraphics().getSprite(t_name), Rectangle(game_->getGraphics().getSprite(t_name)->getWidth(), game_->getGraphics().getSprite(t_name)->getHeight()), attr1.AsInt(), attr2.AsInt() - 64);

		gameObjects.push_back(newtile);
		if (!dontcollide)
		{
			platforms.push_back(newtile->getRect());
			platforms.back().Translate(newtile->getX(), newtile->getY());
		}

	}


}

