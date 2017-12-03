#include "Player.h"
#include "CollisionDetection.h"


void Player::PlayerCollision(std::vector<Rectangle> platforms)
{
	p_groundunder = false;

	Rectangle playerfeet;
	Rectangle playerleft;
	Rectangle playerright;
	Rectangle player3;
	
	playerfeet = Rectangle(this->getTexture()->getWidth() - 8, 4);
	playerleft = Rectangle(2, this->getTexture()->getHeight() - 2);
	playerright = Rectangle(2, this->getTexture()->getHeight() - 2);
	player3 = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight() - 2);

	playerfeet.Translate(getX() + 4, getY() + 44);
	playerleft.Translate(getX() - 2, getY() - 1);
	playerright.Translate(getX() + 48 + 2, getY() - 1);
	player3.Translate(getX(), getY() - 1);

	p_leftCol = false;
	p_rightCol = false;
	p_Col = false;

	for (int i = 0; i < platforms.size(); i++)
	{

		if (CollisionDetection::CheckCollision(playerfeet, platforms[i]))
		{
			p_groundunder = true;
			p_isFalling = false;
			break;
		}
		else
		{
			p_groundunder = false;
			p_isFalling = true;
		}
	}

	for (int i = 0; i < platforms.size(); i++)
	{
		if (CollisionDetection::CheckCollision(playerright, platforms[i]))
		{
			p_rightCol = true;
			break;
		}


	}

	for (int i = 0; i < platforms.size(); i++)
	{
		if (CollisionDetection::CheckCollision(playerleft, platforms[i]))
		{
			p_leftCol = true;
			break;
		}


	}

	for (int i = 0; i < platforms.size(); i++)
	{
		if (CollisionDetection::CheckCollision(player3, platforms[i]))
		{
			p_Col = true;
			break;
		}
	}

}

void Player::PlayerMovement()
{
	//SPRINTING
	//Checks whether the Left Shift key is being pressed. If it is and the Player is not in the middle of falling or jumping, change the speed;
	if (keyData.scanCode[HK_LSHIFT] && !p_isFalling && !p_isJumping)
	{
		p_isSprinting = true;
		p_speed = 4;
	}
	if (!keyData.scanCode[HK_LSHIFT] && !p_isFalling && !p_isJumping)
		p_isSprinting = false;

	if (!p_isSprinting)
		p_speed = 2;

	//FORCE DOWN
	if (!p_isJumping && !p_groundunder)
	{
		setY(getY() + p_jumpspeed);
		//playerGrounded = true;
	}

	//MOVE PLAYER
	bool p_isMoving = false;

	if (keyData.scanCode['A'])
	{
		p_isMoving = true;
		p_isLeft = true;
		p_isRight = false;
		//ANIMATION
		/*
		if (!p_isJumping && !p_isFalling)
		{
			if (p_isSprinting)
				//playerSprite = playerSprites_LeftRun;
			else
				//playerSprite = playerSprites_LeftSprint;
		}
		if (p_isJumping)
		{
			//playerSprite = playerSprites_LeftJump;
		}
		if (p_isFalling && !p_isJumping)
		{
			//playerSprite = playerSprites_LeftFall;
		}
		*/
		if (!p_leftCol)
			setX(getX() - p_speed);

		if (getX() < 0)
		{
			setX(0);
		}


	}

	if (keyData.scanCode['D'])
	{
		p_isMoving = true;
		p_isLeft = false;
		p_isRight = true;
		//ANIMATIoN
		/*
		if (!p_isJumping)
		{
			if (p_isSprinting)
				playerSprite = playerSprites_RightRun;
			else
				playerSprite = playerSprites_RightSprint;
		}
		if (p_isJumping)
		{
			playerSprite = playerSprites_RightJump;
		}
		if (p_isFalling && !p_isJumping)
		{
			playerSprite = playerSprites_RightFall;
		}
		*/
		if (!p_rightCol)
			setX(getX() + p_speed);
	}

	/* ANIMATION
		if (!game_->getKeyboard().scanCode['A'] && player && isLeft && !player_isJumping)
		{
			playerSprite = playerSprites_LeftIdle;
		}

		if (!game_->getKeyboard().scanCode['D'] && player && isRight && !player_isJumping)
		{
			playerSprite = playerSprites_RightIdle;
		}
	*/

	if (p_isFalling && !p_isJumping)
	{
		if (p_isLeft)
		{
			//playerSprite = playerSprites_LeftFall;
		}
		if (p_isRight)
		{
			//playerSprite = playerSprites_RightFall;
		}
	}
	if (!p_isFalling && !p_isJumping && !p_isMoving)
	{
		if (p_isLeft)
		{
			//playerSprite = playerSprites_LeftIdle;
		}
			
		if (p_isRight)
		{
			//playerSprite = playerSprites_RightIdle;
		}
	}

	if ((keyData.scanCode['W'] || keyData.scanCode[HK_SPACE]))
	{
		if (!p_isJumping && !p_isFalling)
		{
			if (p_isLeft)
			{
				//playerSprite = playerSprites_LeftJump;
			}
			if (p_isRight)
			{
				//playerSprite = playerSprites_RightJump;
			}
			if (!p_isLeft && !p_isRight)
			{
				//playerSprite = playerSprites_RightJump;
				p_isRight = true;
			}
			PlayerJump();
		}
	}
	if (p_isJumping)
	{
		//playerGrounded = false;
		PlayerJump();;
	}

}

void Player::PlayerJump()
{
	if (!p_isJumping)
	{
		p_isJumping = true;
		p_jumpingtime = gameClock + 900;

	}

	if (p_isJumping)
	{
		if (gameClock > p_jumpingtime)
		{
			p_isJumping = false;
			if (p_Col)
			{

				//player->setY(player->getY() - jumpspeed);
			}
			else
			{
				p_isFalling = true;
				//player->setY(player->getY() + jumpspeed);
			}
		}
		else
		{
			if (gameClock < p_jumpingtime - 150)
				setY(getY() - p_jumpspeed);
			if (p_Col)
			{
				p_jumpingtime = gameClock - 1;
			}
		}

	}
}


Player::~Player()
{

	delete pAnim_LeftRun;
	delete pAnim_RightRun;
	delete pAnim_LeftSprint;
	delete pAnim_RightSprint;
	delete pAnim_LeftJump;
	delete pAnim_RightJump;
}

void Player::PlayerUpdate()
{
	gameClock = HAPI.GetTime();
	PlayerMovement();
}

void Player::MakeAnims()
{
}
