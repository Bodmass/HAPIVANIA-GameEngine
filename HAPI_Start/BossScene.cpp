#include "BossScene.h"
#include "Game.h"
#include "CollisionDetection.h"

BossScene::~BossScene()
{

	delete playerSprites_LeftRun;
	delete playerSprites_LeftUpRun;
	delete playerSprites_RightUpRun;
	delete playerSprites_RightRun;
	delete playerSprites_LeftSprint;
	delete playerSprites_RightSprint;
	delete playerSprites_LeftJump;
	delete playerSprites_RightJump;

	delete spacePirate_LeftRun;
	delete spacePirate_RightRun;

	delete bat_LeftRun;
	delete bat_RightRun;

	delete ship_Idle;

	delete CamRect;

	for (auto* gameObject : gameObjects)
	{
		delete gameObject;
	}

	for (auto* UI : gameUI)
	{
		delete UI;
	}

	for (auto* enemy : enemies)
	{
		delete enemy;
	}
}


void BossScene::StartBoss()
{
	player->setY(593);
	Sound::stopMusic("BGM 2");
	Sound::playMusic("Boss");
	Sound::playSound("Shoot 2");
	CameraLocked = true;
	BossActivated = true;
}

void BossScene::update()
{
	gameClock = HAPI.GetTime();
	if (!BGMPlaying)
	{
		//if (game_->p_SprintU_Get())
			player->setSprintUpgrade();
		//if (game_->p_XRAYB_Get())
			player->setXRAYUpgrade();
		//if (game_->p_SuperJump_Get())
			player->setJumpUpgrade();

		game_->setCamera(0, 0);
		game_->setRoom("Boss");
		Sound::playMusic("BGM 2");
		BGMPlaying = true;
		GameStarted = true;

		for (auto e : enemies)
		{
			if (game_->isHardMode())
				e->setHardMode();
		}
	}

	if (GameStarted)
	{
		//std::cout << player->getX() << ", " << player->getY() << std::endl;
		CamRect->Translate(-game_->getCameraX(), -game_->getCameraY());

		player->checkHit(bossBullets, 5);
		player->PlayerCollision(platforms, *CamRect);

		if(!BossActivated)
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
					if (b->getTexture() != game_->getGraphics().getSprite("Player_Bullet_1"))
						b->setTexture(game_->getGraphics().getSprite("Player_Bullet_1"));

					if (b->checkUp())
					{
						if (b->getTexture() != game_->getGraphics().getSprite("Player_Bullet_1_Up"))
							b->setTexture(game_->getGraphics().getSprite("Player_Bullet_1_Up"));
					}

					b->CheckCollision(platforms);
				}
				else
				{
					b->setDamage(40);
					if (b->getTexture() != game_->getGraphics().getSprite("Player_Bullet_2"))
						b->setTexture(game_->getGraphics().getSprite("Player_Bullet_2"));

					if (b->checkUp())
					{
						if (b->getTexture() != game_->getGraphics().getSprite("Player_Bullet_2_Up"))
							b->setTexture(game_->getGraphics().getSprite("Player_Bullet_2_Up"));
					}
				}
			}
		}

		

		for (auto b : bossBullets)
		{
			if (b->checkActive())
			{
				b->Update(player->getX(), player->getY());
				
			}
		}

		if (!CameraLocked)
		{
			if (player->getX() >= 1440 && !doorDestroyed)
				StartBoss();

			int distancefromcameraX = abs((player->getX() + 48) - (game_->getScreenWidth() / 2));

			if (player->getX() + 48 > (game_->getScreenWidth() / 2))
			{
				game_->setCamera(-distancefromcameraX, game_->getCameraY());
			}
			else
				game_->setCamera(0, game_->getCameraY());
		}
		


		if (!player->p_CheckAlive())
		{
			Sound::stopMusic("Boss");
			game_->switchScene_Death();
		}

		for (auto p : pickups)
		{
			if (CamRect->rOutside(p->getRect()))
				p->Update(player);
		}

		for (auto e : enemies)
		{
			e->checkHit(bulletObjects);
			e->Update(player, platforms, *CamRect);
			if (dynamic_cast<Boss*>(e)->Shoot(bossBullets, player))
			{
				std::rotate(bossBullets.begin(), bossBullets.begin() + 2, bossBullets.end());
			}


		}


	}

	if (Ship->checkDead())
	{
		if (!musicstopped)
		{
			Sound::stopMusic("Boss");
			musicstopped = true;
		}

		float deltaX = (float)(1440 - Ship->getX());
		float deltaY = (float)(600 - Ship->getY());
		float delta = atan2(deltaY, deltaX);

		Ship->setX(Ship->getX() + (int)(5 * cos(delta)));
		Ship->setY(Ship->getY() + (int)(5 * sin(delta)));

		if ((Ship->getX() >= 1440) && (Ship->getY() >= 600))
		{
			
			game_->switchScene_End();			
		}
	}

	if (BossActivated)
	{
		player->setTexture(playerSprites_RightIdle);

		if (Ship->getY() <= 100)
		{
			Ship->setY(Ship->getY() + 1);
		}


		if (!doorDestroyed)
		{
			float deltaX = (float)(1000 - doorDestroy->getX());
			float deltaY = (float)(600 - doorDestroy->getY());
			float delta = atan2(deltaY, deltaX);

			doorDestroy->setX(doorDestroy->getX() + (int)(5 * cos(delta)));
			doorDestroy->setY(doorDestroy->getY() + (int)(5 * sin(delta)));
		}

		if ((doorDestroy->getX() >= 1000) && (doorDestroy->getY() >= 600))
		{
			if (!doorDestroyed)
			{
				doorDestroy->setX(doorDestroy->getX() - 300);
				loadLevel("Data/DemoLevel2-1.xml");
				Sound::playSound("Shoot 2"); //explosion here
				doorDestroyed = true;

			}
		}

		if ((Ship->getY() >= 100) && doorDestroyed)
		{
			
			Ship->Activate();
			BossActivated = false;
		}
	}

	bool PauseHit = false; 

	if (game_->getController().digitalButtons[HK_DIGITAL_SELECT] || game_->getKeyboard().scanCode[HK_ESCAPE])
		PauseHit = true;


	if (PauseHit && !game_->getPauseLock())
	{
		game_->setRoom("Boss");
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

void BossScene::render()
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


	for (auto* UI : gameUI)
	{
		if (UI->getTexture()->getAlpha())
			game_->getGraphics().BlitAlpha(game_->getScreen(), game_->getScreenRect(), UI->getTexture(), UI->getX(), UI->getY(), game_->getCameraX(), game_->getCameraY());
		else
			game_->getGraphics().Blit(game_->getScreen(), game_->getScreenRect(), UI->getTexture(), UI->getX(), UI->getY(), game_->getCameraX(), game_->getCameraY());
	}

	HAPI.RenderText(10, 10, HAPI_TColour::WHITE, std::to_string(player->p_getcurHP()), 34);
}

void BossScene::loadTextures()
{
	game_->getGraphics().loadTexture("Ship_1", "Textures/AI/BossShip/Ship_01.png"); 
	game_->getGraphics().loadTexture("Ship_2", "Textures/AI/BossShip/Ship_02.png");
	game_->getGraphics().loadTexture("Ship_3", "Textures/AI/BossShip/Ship_03.png");
	game_->getGraphics().loadTexture("Ship_4", "Textures/AI/BossShip/Ship_04.png");
	game_->getGraphics().loadTexture("Ship_Bomb", "Textures/AI/BossShip/Bomb.png");
	game_->getGraphics().loadTexture("Ship_Bullet1", "Textures/AI/BossShip/Ship_Bullet1.png");
	game_->getGraphics().loadTexture("Ship_Missile", "Textures/AI/BossShip/Ship_Missile.png");

	playerSprites_LeftRun = new SpriteAnimator();
	playerSprites_RightRun = new SpriteAnimator();
	playerSprites_LeftUpRun = new SpriteAnimator();
	playerSprites_RightUpRun = new SpriteAnimator();
	playerSprites_LeftSprint = new SpriteAnimator();
	playerSprites_RightSprint = new SpriteAnimator();
	playerSprites_LeftJump = new SpriteAnimator();
	playerSprites_RightJump = new SpriteAnimator();
	spacePirate_LeftRun = new SpriteAnimator();
	spacePirate_RightRun = new SpriteAnimator();
	bat_LeftRun = new SpriteAnimator();
	bat_RightRun = new SpriteAnimator();
	ship_Idle = new SpriteAnimator();


	ship_Idle->addFrame(game_->getGraphics().getSprite("Ship_1"));
	ship_Idle->addFrame(game_->getGraphics().getSprite("Ship_2"));
	ship_Idle->addFrame(game_->getGraphics().getSprite("Ship_3"));
	ship_Idle->addFrame(game_->getGraphics().getSprite("Ship_4"));
	ship_Idle->play();
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

	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_1"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_2"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_3"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_4"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_5"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_6"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_7"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_8"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_9"));
	playerSprites_RightUpRun->addFrame(game_->getGraphics().getSprite("Player_Right_Up_Run_10"));
	playerSprites_RightUpRun->play();

	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_1"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_2"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_3"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_4"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_5"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_6"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_7"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_8"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_9"));
	playerSprites_LeftUpRun->addFrame(game_->getGraphics().getSprite("Player_Left_Up_Run_10"));
	playerSprites_LeftUpRun->play();

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

	spacePirate_RightRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunRight_1"));
	spacePirate_RightRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunRight_2"));
	spacePirate_RightRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunRight_3"));
	spacePirate_RightRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunRight_4"));
	spacePirate_RightRun->play();

	spacePirate_LeftRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunLeft_1"));
	spacePirate_LeftRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunLeft_2"));
	spacePirate_LeftRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunLeft_3"));
	spacePirate_LeftRun->addFrame(game_->getGraphics().getSprite("Enemy_SP_RunLeft_4"));
	spacePirate_LeftRun->play();

	bat_LeftRun->addFrame(game_->getGraphics().getSprite("Enemy_Bat_RunLeft_1"));
	bat_LeftRun->addFrame(game_->getGraphics().getSprite("Enemy_Bat_RunLeft_2"));
	bat_LeftRun->play();

	bat_RightRun->addFrame(game_->getGraphics().getSprite("Enemy_Bat_RunRight_1"));
	bat_RightRun->addFrame(game_->getGraphics().getSprite("Enemy_Bat_RunRight_2"));
	bat_LeftRun->play();

	playerSprites_RightJump->addFrame(game_->getGraphics().getSprite("Player_Right_Jump_3"));
	playerSprites_LeftJump->addFrame(game_->getGraphics().getSprite("Player_Left_Jump_3"));


	playerSprites_LeftIdle = game_->getGraphics().getSprite("Player_Left_Idle");
	playerSprites_RightIdle = game_->getGraphics().getSprite("Player_Right_Idle");
	playerSprites_LeftUpIdle = game_->getGraphics().getSprite("Player_Left_Up_Idle");
	playerSprites_RightUpIdle = game_->getGraphics().getSprite("Player_Right_Up_Idle");
	playerSprites_RightIdle->setEntity();
	playerSprites_LeftIdle->setEntity();
	playerSprite = game_->getGraphics().getSprite("Player_Idle");
	playerSprites_LeftFall = game_->getGraphics().getSprite("Player_Left_Fall_2");
	playerSprites_LeftFall->setEntity();
	playerSprites_RightFall = game_->getGraphics().getSprite("Player_Right_Fall_2");
	playerSprites_RightFall->setEntity();
}

void BossScene::loadGameObject()
{
	BG = new GameObject(game_->getGraphics().getSprite("Background"), Rectangle(game_->getGraphics().getSprite("Background")->getWidth(), game_->getGraphics().getSprite("Background")->getHeight()), 0, 0, true);
	Ship = new Boss(game_->getGraphics().getSprite("Ship_1"), Rectangle(game_->getGraphics().getSprite("Ship_1")->getWidth(), game_->getGraphics().getSprite("Ship_1")->getHeight()), 1350, -200);
	doorDestroy = new GameObject(game_->getGraphics().getSprite("Ship_Bomb"), Rectangle(game_->getGraphics().getSprite("Ship_Bomb")->getWidth(), game_->getGraphics().getSprite("Ship_Bomb")->getHeight()), 1350, -200);
	player = new Player(playerSprite, playerRect, 80, 593);
	HUDBar = new GameObject(game_->getGraphics().getSprite("HUDBar"), Rectangle(game_->getGraphics().getSprite("HUDBar")->getWidth(), game_->getGraphics().getSprite("HUDBar")->getHeight()), 0, 0, true);
	CamRect = new Rectangle(game_->getScreenWidth(), game_->getScreenHeight());

	enemies.push_back(Ship);
	gameObjects.push_back(BG);
	gameObjects.push_back(doorDestroy);
	gameObjects.push_back(player);
	gameUI.push_back(HUDBar);

	for (int i = 0; i < 14; i++)
	{
		Bullet* newbullet = new Bullet(game_->getGraphics().getSprite("Player_Bullet_1"), Rectangle(game_->getGraphics().getSprite("Player_Bullet_1")->getWidth(), game_->getGraphics().getSprite("Player_Bullet_1")->getHeight()), -100, -100);
		gameObjects.push_back(newbullet);
		bulletObjects.push_back(newbullet);
	}

	for (int i = 0; i < 14; i++)
	{
		Bullet* newbullet = new Bullet(game_->getGraphics().getSprite("Ship_Bullet1"), Rectangle(game_->getGraphics().getSprite("Ship_Bullet1")->getWidth(), game_->getGraphics().getSprite("Ship_Bullet1")->getHeight()), -100, -100);
		gameObjects.push_back(newbullet);
		bossBullets.push_back(newbullet);
	}


	player->set_pSprite(playerSprite);
	player->set_pSprite_LeftIdle(playerSprites_LeftIdle);
	player->set_pSprite_RightIdle(playerSprites_RightIdle);
	player->set_pSprite_LeftUpIdle(playerSprites_LeftUpIdle);
	player->set_pSprite_RightUpIdle(playerSprites_RightUpIdle);
	player->set_pSprite_LeftFall(playerSprites_LeftFall);
	player->set_pSprite_RightFall(playerSprites_RightFall);
	player->set_pAnim_LeftRun(playerSprites_LeftRun);
	player->set_pAnim_RightRun(playerSprites_RightRun);
	player->set_pAnim_LeftUpRun(playerSprites_LeftUpRun);
	player->set_pAnim_RightUpRun(playerSprites_RightUpRun);
	player->set_pAnim_LeftJump(playerSprites_LeftJump);
	player->set_pAnim_RightJump(playerSprites_RightJump);
	player->set_pAnim_LeftSprint(playerSprites_LeftSprint);
	player->set_pAnim_RightSprint(playerSprites_RightSprint);
	Ship->set_pSprite_Idle(ship_Idle);

}

void BossScene::loadSounds()
{
	Sound::addMusic("Boss", "Audio/BGM/Boss.ogg");
}

void BossScene::loadLevel(std::string level)
{

	CHapiXML levelxml = level;

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





		GameObject* newtile = new GameObject(game_->getGraphics().getSprite(t_name), Rectangle(game_->getGraphics().getSprite(t_name)->getWidth(), game_->getGraphics().getSprite(t_name)->getHeight()), attr1.AsInt(), attr2.AsInt());

		gameObjects.push_back(newtile);
		if (!dontcollide)
		{
			platforms.push_back(newtile->getRect());
			platforms.back().Translate(newtile->getX(), newtile->getY());
		}

	}

}
