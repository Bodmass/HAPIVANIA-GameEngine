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


}


void GameScene::update()
{
	if (!BGMPlaying)
	{
		HAPI.PlayStreamedMedia("Audio/BGM/Stage1.mp3");
		BGMPlaying = true;
	}

		


		//player->setTexture(dynamic_cast<Texture*>(playerSprites_LeftRun));

		//playerSprite = playerSprites_RightRun;
		//player->setTexture(playerSprites_RightRun);


		/*
		if (controllerData.isAttached)
		{

		HAPI.RenderText(screenWidth - 130, 0, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2, "is Attached!", 22);

		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
		graphics.getSprite(1)->getPosY() += 1;
		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_UP])
		graphics.getSprite(1)->getPosY() -= 1;
		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_LEFT])
		graphics.getSprite(1)->getPosX() -= 1;
		if (controllerData.digitalButtons[HK_DIGITAL_DPAD_RIGHT])
		graphics.getSprite(1)->getPosX() += 1;

		if (graphics.getSprite(1)->getPosY() > screenHeight / 2 - 100 && graphics.getSprite(1)->getPosY() < screenHeight / 2 + 100)
		{
		if (graphics.getSprite(1)->getPosX() > screenWidth / 2 - 100 && graphics.getSprite(1)->getPosX() < screenWidth / 2 + 100)
		HAPI.SetControllerRumble(0, 15000, 15000);
		else
		HAPI.SetControllerRumble(0, 0, 0);
		}
		else
		HAPI.SetControllerRumble(0, 0, 0);
		}
		*/

		//std::cout << player->getX() << " , " << player->getY() << std::endl;

		//playerSprint = false;

		player->PlayerCollision(platforms);
		player->PlayerUpdate();

		



		//SET CAMERA

		int distancefromcameraX = abs((player->getX() + 48) - (game_->getScreenWidth() / 2));
		int distancefromcameraY = abs(player->getY() - (game_->getScreenHeight() / 2));
		
		if (player->getX() + 48 > (game_->getScreenWidth() / 2))
		{
			//distancefromcamera -= 450;
			game_->setCamera(-distancefromcameraX, game_->getCameraY());
		}
		else
			game_->setCamera(0, game_->getCameraY());

		if (player->getY() < (game_->getScreenHeight() / 2))
		{
			//distancefromcamera -= 450;
			game_->setCamera(game_->getCameraX(), distancefromcameraY);
		}

		//IDLE SETTERS



		 /*
		int yt = (game_->getScreenHeight()/2 - (game_->getCameraY() - game_->getScreenHeight() / 2));

		if (player->getY() < (game_->getCameraY() + game_->getScreenHeight() / 2))
			game_->setCamera(game_->getCameraX(), (game_->getScreenHeight() / 2 + (game_->getCameraY() - game_->getScreenHeight() / 2) + playerSpeed));

		if ((player->getY() > (game_->getCameraY() - game_->getScreenHeight() / 2)) && game_->getCameraY > 0)
			game_->setCamera(game_->getCameraX(), (game_->getScreenHeight() / 2 + (game_->getCameraY() - game_->getScreenHeight() / 2) - playerSpeed));

			*/

		//player->getRect() = Rectangle(game_->getGraphics().getSprite(3)->getWidth(), game_->getGraphics().getSprite(3)->getHeight());


		if (player && platforms.size() >= 2)
		{
			player->getRect().Move(player->getX(), player->getY());
			platforms[0].Move(platform1->getX(), platform1->getY());
			platforms[1].Move(platform2->getX(), platform2->getY());
		}

		if (game_->getKeyboard().scanCode[HK_UP])
		{
			game_->setCamera(game_->getCameraX(), game_->getCameraY() - 1);
		}
		if (game_->getKeyboard().scanCode[HK_DOWN])
		{
			game_->setCamera(game_->getCameraX(), game_->getCameraY() + 1);
		}

		//std::cout << player->getX() << "," << player->getY() << std::endl;

		//player->setTexture(playerSprite);
		playerRect = Rectangle(game_->getGraphics().getSprite(3)->getWidth(), game_->getGraphics().getSprite(3)->getHeight());
		player->setRectangle(playerRect);

		if (game_->getKeyboard().scanCode[HK_ESCAPE] && !game_->getPauseLock())
		{
			game_->setPauseLock(true);
			game_->switchScene_Pause();
			//TEMP HERE
			game_->p_SprintU_Set(player->checkSprintUpgrade());
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
}

void GameScene::loadTextures()
{
	game_->getGraphics().loadTexture("Textures/Level/BGs/BG1.tga", false); //0 - BG -
	game_->getGraphics().loadTexture("Data/test.tga", false); //1 - Platform 1 -
	game_->getGraphics().loadTexture("Data/platform1.tga", false); //2 - Platform 2 - 

	//PLAYER//
	//IDLE
	game_->getGraphics().loadTexture("Textures/Player/Player_01.png"); //3 - Player - 
	//LEFT IDLE
	game_->getGraphics().loadTexture("Textures/Player/Player_12.png"); //4
	//LEFT RUN
	leftRunStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Textures/Player/Player_13.png"); //5
	game_->getGraphics().loadTexture("Textures/Player/Player_14.png"); //6
	game_->getGraphics().loadTexture("Textures/Player/Player_15.png"); //7
	game_->getGraphics().loadTexture("Textures/Player/Player_16.png"); //8
	game_->getGraphics().loadTexture("Textures/Player/Player_17.png"); //9
	game_->getGraphics().loadTexture("Textures/Player/Player_18.png"); //10
	game_->getGraphics().loadTexture("Textures/Player/Player_19.png"); //11
	game_->getGraphics().loadTexture("Textures/Player/Player_20.png"); //12
	game_->getGraphics().loadTexture("Textures/Player/Player_21.png"); //13
	game_->getGraphics().loadTexture("Textures/Player/Player_22.png"); //14
	//RIGHT IDLE
	game_->getGraphics().loadTexture("Textures/Player/Player_23.png"); //15
	//RIGHT RUN
	rightRunStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Textures/Player/Player_24.png"); //16
	game_->getGraphics().loadTexture("Textures/Player/Player_25.png"); //17
	game_->getGraphics().loadTexture("Textures/Player/Player_26.png"); //18
	game_->getGraphics().loadTexture("Textures/Player/Player_27.png"); //19
	game_->getGraphics().loadTexture("Textures/Player/Player_28.png"); //20
	game_->getGraphics().loadTexture("Textures/Player/Player_29.png"); //21
	game_->getGraphics().loadTexture("Textures/Player/Player_30.png"); //22
	game_->getGraphics().loadTexture("Textures/Player/Player_31.png"); //23
	game_->getGraphics().loadTexture("Textures/Player/Player_32.png"); //24
	game_->getGraphics().loadTexture("Textures/Player/Player_33.png"); //25
	//LEFT SPRINT
	leftSprintStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Textures/Player/Player_34.png"); //26
	game_->getGraphics().loadTexture("Textures/Player/Player_35.png"); //27
	game_->getGraphics().loadTexture("Textures/Player/Player_36.png"); //28
	game_->getGraphics().loadTexture("Textures/Player/Player_37.png"); //29
	game_->getGraphics().loadTexture("Textures/Player/Player_38.png"); //30
	game_->getGraphics().loadTexture("Textures/Player/Player_39.png"); //31
	game_->getGraphics().loadTexture("Textures/Player/Player_40.png"); //32
	game_->getGraphics().loadTexture("Textures/Player/Player_41.png"); //33
	game_->getGraphics().loadTexture("Textures/Player/Player_42.png"); //34
	game_->getGraphics().loadTexture("Textures/Player/Player_43.png"); //35
	//RIGHT SPRINT
	rightSprintStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Textures/Player/Player_45.png"); //36
	game_->getGraphics().loadTexture("Textures/Player/Player_46.png"); //37
	game_->getGraphics().loadTexture("Textures/Player/Player_47.png"); //38
	game_->getGraphics().loadTexture("Textures/Player/Player_48.png"); //39
	game_->getGraphics().loadTexture("Textures/Player/Player_49.png"); //40
	game_->getGraphics().loadTexture("Textures/Player/Player_50.png"); //41
	game_->getGraphics().loadTexture("Textures/Player/Player_51.png"); //42
	game_->getGraphics().loadTexture("Textures/Player/Player_52.png"); //43
	game_->getGraphics().loadTexture("Textures/Player/Player_53.png"); //44
	game_->getGraphics().loadTexture("Textures/Player/Player_54.png"); //45
	//LEFT JUMP
	leftJumpStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Textures/Player/Player_61.png"); //46
	game_->getGraphics().loadTexture("Textures/Player/Player_62.png"); //47
	game_->getGraphics().loadTexture("Textures/Player/Player_63.png"); //48
	game_->getGraphics().loadTexture("Textures/Player/Player_64.png"); //49
	game_->getGraphics().loadTexture("Textures/Player/Player_65.png"); //50
	game_->getGraphics().loadTexture("Textures/Player/Player_66.png"); //51
	//RIGHT JUMP
	rightJumpStartIndex = game_->getGraphics().spriteMapSize();
	game_->getGraphics().loadTexture("Textures/Player/Player_73.png"); //52
	game_->getGraphics().loadTexture("Textures/Player/Player_74.png"); //53
	game_->getGraphics().loadTexture("Textures/Player/Player_75.png"); //54
	game_->getGraphics().loadTexture("Textures/Player/Player_76.png"); //55
	game_->getGraphics().loadTexture("Textures/Player/Player_77.png"); //56
	game_->getGraphics().loadTexture("Textures/Player/Player_78.png"); //57
	//END OF PLAYER//
	
	playerSprites_LeftRun = new SpriteAnimator();
	playerSprites_RightRun = new SpriteAnimator();
	playerSprites_LeftSprint = new SpriteAnimator();
	playerSprites_RightSprint = new SpriteAnimator();
	playerSprites_LeftJump = new SpriteAnimator();
	playerSprites_RightJump = new SpriteAnimator();

	//playerSprites_LeftRun->addFrame(game_->getGraphics().getSprite(3));
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
	playerSprites_LeftJump->play();

	playerSprites_LeftIdle = game_->getGraphics().getSprite(4);
	playerSprites_RightIdle = game_->getGraphics().getSprite(15);
	playerSprites_RightIdle->setEntity();
	playerSprites_LeftIdle->setEntity();
	playerSprite = game_->getGraphics().getSprite(3);
	playerSprites_LeftFall = game_->getGraphics().getSprite(51);
	playerSprites_LeftFall->setEntity();
	playerSprites_RightFall = game_->getGraphics().getSprite(57);
	playerSprites_RightFall->setEntity();

	

}

void GameScene::loadGameObject()
{
	BG = new GameObject(game_->getGraphics().getSprite(0), Rectangle(game_->getGraphics().getSprite(0)->getWidth(), game_->getGraphics().getSprite(0)->getHeight()), 0, 0, true);
	//player = new GameObject(game_->getGraphics().getSprite(3), Rectangle(game_->getGraphics().getSprite(3)->getWidth(), game_->getGraphics().getSprite(3)->getHeight()), 20, 0);
	player = new Player(playerSprite, playerRect, 60, 352);
	platform1 = new GameObject(game_->getGraphics().getSprite(1), Rectangle(game_->getGraphics().getSprite(1)->getWidth(), game_->getGraphics().getSprite(1)->getHeight()), 0, 400);
	platform2 = new GameObject(game_->getGraphics().getSprite(2), Rectangle(game_->getGraphics().getSprite(2)->getWidth(), game_->getGraphics().getSprite(2)->getHeight()), 300, 300);

	gameObjects.push_back(BG);
	gameObjects.push_back(player);
	gameObjects.push_back(platform1);
	gameObjects.push_back(platform2);

	platforms.push_back(platform1->getRect());
	platforms.push_back(platform2->getRect());

	platforms[0].Translate(platform1->getX(), platform1->getY());
	platforms[1].Translate(platform2->getX(), platform2->getY());

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

