#include "GameScene.h"
#include "Game.h"
#include "CollisionDetection.h"

#include "Enemy_SP.h"
#include "Enemy_Bat.h"

GameScene::~GameScene()
{

	delete playerSprites_LeftRun;
	delete playerSprites_RightRun;
	delete playerSprites_LeftUpRun;
	delete playerSprites_RightUpRun;
	delete playerSprites_LeftSprint;
	delete playerSprites_RightSprint;
	delete playerSprites_LeftJump;
	delete playerSprites_RightJump;
	delete spacePirate_LeftRun;
	delete spacePirate_RightRun;
	delete bat_LeftRun;
	delete bat_RightRun;

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


void GameScene::update()
{

	gameClock = HAPI.GetTime();

	if (game_->CheckReset())
	{
		//Reset();

	}

	if (!Setup)
	{
		player->PlayerUpdate();
		GameStartWait = gameClock;
		game_->setRoom("Demo");
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

			for (auto e : enemies)
			{
				if (game_->isHardMode())
					e->setHardMode();

				e->Setup();
			}

			player->setX(playerspawnx);
			player->setY(playerspawny);

		}
	}

	if (GameStarted)
	{

		//Translate the CamRect to the position of the Camera X and Y
		
		CamRect->Translate(-game_->getCameraX(), -game_->getCameraY());

		//Player Updates
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
				if(player->checkXRAYUpgrade())
					b->setDamage(40);

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
		
		for (auto p : pickups)
		{
			//If the pickout is outside the Camera View, Don't update.
			if(CamRect->rOutside(p->getRect()))
				p->Update(player);
		}
		

		
		//Warp Check and if the player is inside of it.
		for (auto w : warps)
		{
			w->Update(&player->getPlayerRect());
			
			if (w->getID() == 1 && w->Entered())
			{
				Sound::stopMusic("BGM 1");
				game_->switchScene_Boss();
				game_->p_SprintU_Set(player->checkSprintUpgrade());
				game_->p_XRAYB_Set(player->checkXRAYUpgrade());
				game_->p_SuperJump_Set(player->checkJumpUpgrade());
			}
		}
		
		//Enemy Update

		for (auto e : enemies)
		{
			e->checkHit(bulletObjects);
			e->Update(player, platforms, *CamRect);
			dynamic_cast<Enemy_Bat*>(e)->BatConflict(e); //Bats Only
			
		}
		
		//If the player falls under the map
		if (player->getY() > (game_->getCameraY() + levelheight))
			player->Attacked(99); //Instant Death


		//If the player's health is depleted
		if (!player->p_CheckAlive())
		{
			Sound::stopMusic("BGM 1");
			game_->switchScene_Death();
		}

		
		/////PAUSE/////
		bool PauseHit = false;

		if (game_->getController().digitalButtons[HK_DIGITAL_SELECT] || game_->getKeyboard().scanCode[HK_ESCAPE])
			PauseHit = true;

		if (PauseHit && !game_->getPauseLock())
		{
			game_->setPauseLock(true);
			game_->switchScene_Pause();

			game_->p_SprintU_Set(player->checkSprintUpgrade());
			game_->p_XRAYB_Set(player->checkXRAYUpgrade());
			game_->p_SuperJump_Set(player->checkJumpUpgrade());
		}

		if (!PauseHit)
		{
			game_->setPauseLock(false);
		}
		/////PAUSE/////
	}



		//SET CAMERA

		int distancefromcameraX = abs((player->getX() + 48) - (game_->getScreenWidth() / 2));
		int distancefromcameraY = abs(player->getY() - (game_->getScreenHeight() / 2));
		int distancefrombottom = abs(player->getY() - (levelheight));
		
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
		else
		{
			if (levelheight > game_->getScreenHeight())
			{
				if (player->getY() < distancefrombottom)
				{
					game_->setCamera(game_->getCameraX(), -distancefromcameraY);
				}
			}
		}
		


}

void GameScene::render()
{
	if (GameStarted)
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
	else
	{
		HAPI.RenderText(game_->getScreenWidth() / 2 - 200, game_->getScreenHeight() / 2, HAPI_TColour::WHITE, "LOADING", 100);
	}
}

void GameScene::loadTextures()
{
	game_->getGraphics().loadTexture("Background","Textures/Level/BGs/BG1.tga", false);
	game_->getGraphics().loadTexture("HUDBar", "Textures/UI/HUD/HUDBar.png", false);
	//BULLETS
	game_->getGraphics().loadTexture("Player_Bullet_1", "Textures/Player/Bullets/BasicBullet.png"); 
	game_->getGraphics().loadTexture("Player_Bullet_2", "Textures/Player/Bullets/XRAYBullet.png"); 

	game_->getGraphics().loadTexture("Player_Bullet_1_Up", "Textures/Player/Bullets/BasicBullet_Up.png"); 
	game_->getGraphics().loadTexture("Player_Bullet_2_Up", "Textures/Player/Bullets/XRAYBullet_Up.png"); 

	//PICKUPS
	game_->getGraphics().loadTexture("Pickup_Sprint_1", "Textures/Pickups/Sprint/Sprint_0.png"); 
	game_->getGraphics().loadTexture("Pickup_Jump_1", "Textures/Pickups/Sprint/Sprint_1.png"); 
	game_->getGraphics().loadTexture("Pickup_XRAY_1", "Textures/Pickups/Xray/XRAY_0.png"); 

	//ENEMIES

	//SP
	game_->getGraphics().loadTexture("Enemy_SP_FaceLeft", "Textures/AI/SpacePirate/SpacePirate_10.png");
	game_->getGraphics().loadTexture("Enemy_SP_FaceRight", "Textures/AI/SpacePirate/SpacePirate_02.png");

	game_->getGraphics().loadTexture("Enemy_SP_RunRight_1", "Textures/AI/SpacePirate/SpacePirate_05.png");
	game_->getGraphics().loadTexture("Enemy_SP_RunRight_2", "Textures/AI/SpacePirate/SpacePirate_06.png");
	game_->getGraphics().loadTexture("Enemy_SP_RunRight_3", "Textures/AI/SpacePirate/SpacePirate_07.png");
	game_->getGraphics().loadTexture("Enemy_SP_RunRight_4", "Textures/AI/SpacePirate/SpacePirate_08.png");

	game_->getGraphics().loadTexture("Enemy_SP_RunLeft_1", "Textures/AI/SpacePirate/SpacePirate_13.png");
	game_->getGraphics().loadTexture("Enemy_SP_RunLeft_2", "Textures/AI/SpacePirate/SpacePirate_14.png");
	game_->getGraphics().loadTexture("Enemy_SP_RunLeft_3", "Textures/AI/SpacePirate/SpacePirate_15.png");
	game_->getGraphics().loadTexture("Enemy_SP_RunLeft_4", "Textures/AI/SpacePirate/SpacePirate_16.png");

	//BAT
	game_->getGraphics().loadTexture("Enemy_Bat_Idle", "Textures/AI/Bat/Bat_01.png");

	game_->getGraphics().loadTexture("Enemy_Bat_RunRight_1", "Textures/AI/Bat/Bat_04.png");
	game_->getGraphics().loadTexture("Enemy_Bat_RunRight_2", "Textures/AI/Bat/Bat_05.png");
	game_->getGraphics().loadTexture("Enemy_Bat_RunLeft_1", "Textures/AI/Bat/Bat_02.png");
	game_->getGraphics().loadTexture("Enemy_Bat_RunLeft_2", "Textures/AI/Bat/Bat_03.png");

	//PLAYER//
	//IDLE
	game_->getGraphics().loadTexture("Player_Idle","Textures/Player/Player_01.png"); //3 - Player - 
	//LEFT IDLE
	game_->getGraphics().loadTexture("Player_Left_Idle", "Textures/Player/Player_12.png"); //4
	//LEFT RUN
	leftRunStartIndex = (int)game_->getGraphics().spriteMapSize();
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
	rightRunStartIndex = (int)game_->getGraphics().spriteMapSize();
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
	leftSprintStartIndex = (int)game_->getGraphics().spriteMapSize();
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
	rightSprintStartIndex = (int)game_->getGraphics().spriteMapSize();
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
	leftJumpStartIndex = (int)game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Left_Jump_1", "Textures/Player/Player_56.png"); //46
	game_->getGraphics().loadTexture("Player_Left_Jump_2", "Textures/Player/Player_57.png"); //47
	game_->getGraphics().loadTexture("Player_Left_Jump_3", "Textures/Player/Player_58.png"); //48
	game_->getGraphics().loadTexture("Player_Left_Jump_4", "Textures/Player/Player_59.png"); //49
	game_->getGraphics().loadTexture("Player_Left_Fall_1", "Textures/Player/Player_60.png"); //50
	game_->getGraphics().loadTexture("Player_Left_Fall_2", "Textures/Player/Player_61.png"); //51
	//RIGHT JUMP
	rightJumpStartIndex = (int)game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Player_Right_Jump_1", "Textures/Player/Player_67.png"); //52
	game_->getGraphics().loadTexture("Player_Right_Jump_2", "Textures/Player/Player_68.png"); //53
	game_->getGraphics().loadTexture("Player_Right_Jump_3", "Textures/Player/Player_69.png"); //54
	game_->getGraphics().loadTexture("Player_Right_Jump_4", "Textures/Player/Player_70.png"); //55
	game_->getGraphics().loadTexture("Player_Right_Fall_1", "Textures/Player/Player_71.png"); //56
	game_->getGraphics().loadTexture("Player_Right_Fall_2", "Textures/Player/Player_72.png"); //57

	//FACE UP AND LEFT
	
	game_->getGraphics().loadTexture("Player_Left_Up_Idle", "Textures/Player/Player_78.png"); 
	game_->getGraphics().loadTexture("Player_Left_Up_Run_1", "Textures/Player/Player_79.png"); 
	game_->getGraphics().loadTexture("Player_Left_Up_Run_2", "Textures/Player/Player_80.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_3", "Textures/Player/Player_81.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_4", "Textures/Player/Player_82.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_5", "Textures/Player/Player_83.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_6", "Textures/Player/Player_84.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_7", "Textures/Player/Player_85.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_8", "Textures/Player/Player_86.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_9", "Textures/Player/Player_87.png");
	game_->getGraphics().loadTexture("Player_Left_Up_Run_10", "Textures/Player/Player_88.png");
	
	//FACE UP AND RIGHT
	game_->getGraphics().loadTexture("Player_Right_Up_Idle", "Textures/Player/Player_89.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_1", "Textures/Player/Player_90.png"); 
	game_->getGraphics().loadTexture("Player_Right_Up_Run_2", "Textures/Player/Player_91.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_3", "Textures/Player/Player_92.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_4", "Textures/Player/Player_93.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_5", "Textures/Player/Player_94.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_6", "Textures/Player/Player_95.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_7", "Textures/Player/Player_96.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_8", "Textures/Player/Player_97.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_9", "Textures/Player/Player_98.png");
	game_->getGraphics().loadTexture("Player_Right_Up_Run_10", "Textures/Player/Player_99.png");
	
	//END OF PLAYER//
	


	//END OF PLAYER



	

}

void GameScene::loadGameObject()
{
	/*PLAYER*/
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

	/*END OF PLAYER*/
	BG = new GameObject(game_->getGraphics().getSprite("Background"), Rectangle(game_->getGraphics().getSprite("Background")->getWidth(), game_->getGraphics().getSprite("Background")->getHeight()), 0, 0, true);
	player = new Player(playerSprite, playerRect, playerspawnx, playerspawny);
	/*Sprint_PU = new Pickup(1, game_->getGraphics().getSprite("Pickup_Sprint_1"), Rectangle(game_->getGraphics().getSprite("Pickup_Sprint_1")->getWidth(), game_->getGraphics().getSprite("Pickup_Sprint_1")->getHeight()), 2600, 200);
	Pickup* XRAY_PU = new Pickup(3, game_->getGraphics().getSprite("Pickup_XRAY_1"), Rectangle(game_->getGraphics().getSprite("Pickup_XRAY_1")->getWidth(), game_->getGraphics().getSprite("Pickup_XRAY_1")->getHeight()), 2600, 484);
	Pickup* JUMP_PU = new Pickup(2, game_->getGraphics().getSprite("Pickup_Jump_1"), Rectangle(game_->getGraphics().getSprite("Pickup_Jump_1")->getWidth(), game_->getGraphics().getSprite("Pickup_Jump_1")->getHeight()), 5768, 371);*/
	HUDBar = new GameObject(game_->getGraphics().getSprite("HUDBar"), Rectangle(game_->getGraphics().getSprite("HUDBar")->getWidth(), game_->getGraphics().getSprite("HUDBar")->getHeight()), 0, 0, true);
	CamRect = new Rectangle(game_->getScreenWidth(), game_->getScreenHeight());

	gameObjects.push_back(BG);
	gameObjects.push_back(player);

	gameUI.push_back(HUDBar);
	


	//platforms.push_back(Sprint_PU->getRect());

	player->getRect().Translate(player->getX(), player->getY());
	


	//Offscreen Bullets
	for (int i = 0; i < 14; i++)
	{
		Bullet* newbullet = new Bullet(game_->getGraphics().getSprite("Player_Bullet_1"), Rectangle(game_->getGraphics().getSprite("Player_Bullet_1")->getWidth(), game_->getGraphics().getSprite("Player_Bullet_1")->getHeight()), -100, -100);
		gameObjects.push_back(newbullet);
		bulletObjects.push_back(newbullet);
	}

	/*
	//Enemy (Temp here, move into new function)
	Enemy_SP* SpacePirate = new Enemy_SP(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"), Rectangle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getWidth(), game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getHeight()), 610, 467);
	enemies.push_back(SpacePirate);

	int batspawnx = 610;
	for (int i = 0; i < 10; i++)
	{
		Enemy_Bat* Bat = new Enemy_Bat(game_->getGraphics().getSprite("Enemy_Bat_Idle"), Rectangle(game_->getGraphics().getSprite("Enemy_Bat_Idle")->getWidth(), game_->getGraphics().getSprite("Enemy_Bat_Idle")->getHeight()), batspawnx, 130);
		enemies.push_back(Bat);
		batspawnx += 35;
	}

	int spspawn = 1124;
	for (int i = 0; i < 10; i++)
	{

		Enemy_SP* SpacePirates = new Enemy_SP(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"), Rectangle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getWidth(), game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getHeight()), spspawn, 209);
		enemies.push_back(SpacePirates);
		spspawn += 100;
	}

	spspawn = 940;
	for (int i = 0; i < 9; i++)
	{
		
		Enemy_SP* SpacePirate2 = new Enemy_SP(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"), Rectangle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getWidth(), game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getHeight()), spspawn, 467);
		enemies.push_back(SpacePirate2);
		spspawn += 450;
	}

	spspawn = 4144;
	for (int i = 0; i < 4; i++)
	{

		Enemy_SP* SpacePirate3 = new Enemy_SP(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"), Rectangle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getWidth(), game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getHeight()), spspawn, 179);
		enemies.push_back(SpacePirate3);
		spspawn += 450;
	}
	*/


	HUDBar->getRect().Translate(HUDBar->getX(), game_->getScreenHeight() - HUDBar->getRect().getHeight());
	//Sprint_PU->setTexture(game_->getGraphics().getSprite(58));
	

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

	/*/
	for (auto spe : enemies)
	{
		if (dynamic_cast<Enemy_SP*>(spe))
		{
			dynamic_cast<Enemy_SP*>(spe)->set_pAnim_RightRun(spacePirate_RightRun);
			dynamic_cast<Enemy_SP*>(spe)->set_pAnim_LeftRun(spacePirate_LeftRun);
			dynamic_cast<Enemy_SP*>(spe)->set_pSprite_LeftIdle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"));
			dynamic_cast<Enemy_SP*>(spe)->set_pSprite_RightIdle(game_->getGraphics().getSprite("Enemy_SP_FaceRight"));
		}
		if (dynamic_cast<Enemy_Bat*>(spe))
		{
			dynamic_cast<Enemy_Bat*>(spe)->set_pAnim_RightRun(bat_RightRun);
			dynamic_cast<Enemy_Bat*>(spe)->set_pAnim_LeftRun(bat_LeftRun);
			dynamic_cast<Enemy_Bat*>(spe)->set_pSprite_Idle(game_->getGraphics().getSprite("Enemy_Bat_Idle"));
		}
	}
	*/


}

void GameScene::loadSounds()
{
	Sound::addMusic("BGM 1", "Audio/BGM/Stage1.ogg");
	Sound::addMusic("BGM 2", "Audio/BGM/Stage2.ogg");
	Sound::addMusic("Appear", "Audio/SE/Appear.wav");
	Sound::addSound("Shoot 1", "Audio/SE/laser1.wav");
	Sound::addSound("Shoot 2", "Audio/SE/laser2.wav");
	Sound::addSound("Upgrade", "Audio/SE/ItemRecieved.wav");
	Sound::addSound("Damaged 1", "Audio/SE/player_damaged1.wav");
	Sound::addSound("Damaged 2", "Audio/SE/player_damaged2.wav");
	Sound::addSound("Death", "Audio/SE/player_death.wav");
	Sound::addSound("Enemy Damaged 1", "Audio/SE/enemy_damaged1.wav");
	Sound::addSound("Enemy Death", "Audio/SE/enemy_death.wav");
}

void GameScene::Reset()
{

}

void GameScene::loadLevel(std::string level)
{


	CHapiXML levelxml = level;
	//std::cout << "Setting Up Level Sprites: " << level << std::endl;
	std::vector<CHapiXMLNode*> tilesused = levelxml.GetAllNodesWithName("sprite");
	std::vector<CHapiXMLNode*> levelinfo = levelxml.GetAllNodesWithName("info");

	CHapiXMLAttribute heightattr;

	for (auto info : levelinfo)
	{
		if (!info->GetAttributeWithName("height", heightattr))
			return;
		levelheight = heightattr.AsInt();
	}

	if (!game_->Check_GameScene_TilesLoaded())
	{
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
		game_->Set_GameScene_TilesLoaded(true);
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

		if (attr3.AsString() == "Cave/Cave_23.png" || attr3.AsString() == "Cave/Cave_24.png" ||  attr3.AsString() == "Cave/Cave_25.png" || attr3.AsString() == "Cave/Cave_26.png" || attr3.AsString() == "Cave/Cave_27.png" || attr3.AsString() == "Cave/Cave_28.png" || attr3.AsString() == "Cave/Cave_21.png" || attr3.AsString() == "Cave/Cave_20.png" || attr3.AsString() == "Cave/Cave_18.png" || attr3.AsString() == "Cave/Cave_17.png" || attr3.AsString() == "Cave/Cave_08.png" || attr3.AsString() == "Cave/Cave_09.png" || attr3.AsString() == "Cave/Cave_10.png")
		{
			dontcollide = true;
		}

		bool isBossDoor = false;
		if (attr3.AsString() == "Cave/Cave_27.png" || attr3.AsString() == "Cave/Cave_28.png")
		{
			isBossDoor = true;
		}

		std::string t_name = attr3.AsString();

		if (attr3.AsString() == "Misc/images/SpecialTiles_01.png" || attr3.AsString() == "Misc/images/SpecialTiles_02.png" || attr3.AsString() == "Misc/images/SpecialTiles_03.png" || attr3.AsString() == "Misc/images/SpecialTiles_04.png" || attr3.AsString() == "Misc/images/SpecialTiles_05.png" || attr3.AsString() == "Misc/images/SpecialTiles_06.png" || attr3.AsString() == "Misc/images/SpecialTiles_07.png")
		{
			if (attr3.AsString() == "Misc/images/SpecialTiles_01.png")
			{
				playerspawnx = attr1.AsInt();
				playerspawny = attr2.AsInt() - (32 + 18);

			}

			if (attr3.AsString() == "Misc/images/SpecialTiles_02.png")
			{
				Enemy_SP* SpacePirate = new Enemy_SP(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"), Rectangle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getWidth(), game_->getGraphics().getSprite("Enemy_SP_FaceLeft")->getHeight()), attr1.AsInt(), attr2.AsInt() - (32 + 12));
				enemies.push_back(SpacePirate);

			}

			if (attr3.AsString() == "Misc/images/SpecialTiles_03.png")
			{
				Enemy_Bat* Bat = new Enemy_Bat(game_->getGraphics().getSprite("Enemy_Bat_Idle"), Rectangle(game_->getGraphics().getSprite("Enemy_Bat_Idle")->getWidth(), game_->getGraphics().getSprite("Enemy_Bat_Idle")->getHeight()), attr1.AsInt(), attr2.AsInt() - (32));
				enemies.push_back(Bat);

			}

			if (attr3.AsString() == "Misc/images/SpecialTiles_05.png")
			{
				Pickup* Sprint_PU = new Pickup(1, game_->getGraphics().getSprite("Pickup_Sprint_1"), Rectangle(game_->getGraphics().getSprite("Pickup_Sprint_1")->getWidth(), game_->getGraphics().getSprite("Pickup_Sprint_1")->getHeight()), attr1.AsInt(), attr2.AsInt() - (32));
				gameObjects.push_back(Sprint_PU);
				pickups.push_back(Sprint_PU);
				Sprint_PU->getRect().Translate(Sprint_PU->getX(), Sprint_PU->getY());
				
			}

			if (attr3.AsString() == "Misc/images/SpecialTiles_07.png")
			{
				Pickup* XRAY_PU = new Pickup(3, game_->getGraphics().getSprite("Pickup_XRAY_1"), Rectangle(game_->getGraphics().getSprite("Pickup_XRAY_1")->getWidth(), game_->getGraphics().getSprite("Pickup_XRAY_1")->getHeight()), attr1.AsInt(), attr2.AsInt() - (32));
				gameObjects.push_back(XRAY_PU);
				pickups.push_back(XRAY_PU);
				XRAY_PU->getRect().Translate(XRAY_PU->getX(), XRAY_PU->getY());
			}

			if (attr3.AsString() == "Misc/images/SpecialTiles_06.png")
			{
				Pickup* JUMP_PU = new Pickup(2, game_->getGraphics().getSprite("Pickup_Jump_1"), Rectangle(game_->getGraphics().getSprite("Pickup_Jump_1")->getWidth(), game_->getGraphics().getSprite("Pickup_Jump_1")->getHeight()), attr1.AsInt(), attr2.AsInt() - (32));
				gameObjects.push_back(JUMP_PU);
				pickups.push_back(JUMP_PU);
				JUMP_PU->getRect().Translate(JUMP_PU->getX(), JUMP_PU->getY());
			}
		}
		else
		{
			if (isBossDoor)

			{
				Warp* newwarp = new Warp(1, game_->getGraphics().getSprite(t_name), Rectangle(game_->getGraphics().getSprite(t_name)->getWidth(), game_->getGraphics().getSprite(t_name)->getHeight()), attr1.AsInt(), attr2.AsInt() - 32);
				gameObjects.push_back(newwarp);
				warps.push_back(newwarp);
				warps.back()->getRect().Translate(newwarp->getX(), newwarp->getY());
			}


			else
			{


				GameObject* newtile = new GameObject(game_->getGraphics().getSprite(t_name), Rectangle(game_->getGraphics().getSprite(t_name)->getWidth(), game_->getGraphics().getSprite(t_name)->getHeight()), attr1.AsInt(), attr2.AsInt() - 32);

				gameObjects.push_back(newtile);
				if (!dontcollide)
				{
					platforms.push_back(newtile->getRect());
					platforms.back().Translate(newtile->getX(), newtile->getY());
				}
			}
		}



	}

	for (auto spe : enemies)
	{
		if (dynamic_cast<Enemy_SP*>(spe))
		{
			dynamic_cast<Enemy_SP*>(spe)->set_pAnim_RightRun(spacePirate_RightRun);
			dynamic_cast<Enemy_SP*>(spe)->set_pAnim_LeftRun(spacePirate_LeftRun);
			dynamic_cast<Enemy_SP*>(spe)->set_pSprite_LeftIdle(game_->getGraphics().getSprite("Enemy_SP_FaceLeft"));
			dynamic_cast<Enemy_SP*>(spe)->set_pSprite_RightIdle(game_->getGraphics().getSprite("Enemy_SP_FaceRight"));
		}
		if (dynamic_cast<Enemy_Bat*>(spe))
		{
			dynamic_cast<Enemy_Bat*>(spe)->set_pAnim_RightRun(bat_RightRun);
			dynamic_cast<Enemy_Bat*>(spe)->set_pAnim_LeftRun(bat_LeftRun);
			dynamic_cast<Enemy_Bat*>(spe)->set_pSprite_Idle(game_->getGraphics().getSprite("Enemy_Bat_Idle"));
		}
	}


}

