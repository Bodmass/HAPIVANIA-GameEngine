#include "Player.h"
#include "CollisionDetection.h"


void Player::PlayerCollision(std::vector<Rectangle> platforms, Rectangle camRect)
{
	p_groundunder = false;

	playerfeet = Rectangle(this->getTexture()->getWidth() - 6, 4);
	playerleft = Rectangle(1, this->getTexture()->getHeight() - 2);
	playerright = Rectangle(1, this->getTexture()->getHeight() - 2);
	player3 = Rectangle(this->getTexture()->getWidth() - 4, this->getTexture()->getHeight() - 2);

	playerfeet.Translate(getX() + 3, getY() + 44);
	playerleft.Translate(getX() - 1, getY() - 1);
	playerright.Translate(getX() + 48 + 1, getY() - 1);
	player3.Translate(getX() + 2, getY() - 1);

	p_leftCol = false;
	p_rightCol = false;
	p_Col = false;

	
	//Loops between all the Rectangles of the Player between the Platforms around it.
	//If the Distance between the Rectangle and the Platform is greater than 100, the Collision wouldn't be checked.
	for (int i = 0; i < platforms.size(); i++)
	{
		
		int Distance = abs(platforms[i].getLeft() - player3.getLeft());
		
		if (Distance <= 100)
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
	}

	for (int i = 0; i < platforms.size(); i++)
	{
		int Distance = abs(platforms[i].getLeft() - player3.getLeft());

		if (Distance <= 100)
		{
			if (camRect.rOutside(platforms[i]))
			{
				if (CollisionDetection::CheckCollision(playerright, platforms[i]))
				{
					p_rightCol = true;
					break;
				}
			}
		}


	}

	for (int i = 0; i < platforms.size(); i++)
	{
		int Distance = abs(platforms[i].getLeft() - player3.getLeft());

		if (Distance <= 100)
		{
			if (CollisionDetection::CheckCollision(playerleft, platforms[i]))
			{
				p_leftCol = true;
				break;
			}
		}

	}

	for (int i = 0; i < platforms.size(); i++)
	{
		int Distance = abs(platforms[i].getLeft() - player3.getLeft());

		if (Distance <= 100)
		{
			if (CollisionDetection::CheckCollision(player3, platforms[i]))
			{
				p_Col = true;
				break;
			}
		}
	}

}

void Player::PlayerPickup(Rectangle pickup)
{
}

bool Player::PlayerImmunityCheck()
{
	if (!p_Immunity)
	{
		p_Immunity = true;
		p_Immunity_Time = gameClock + (p_Immunity_Delay * 1000);

		return false;
	}

	if(p_Immunity)
		if (gameClock > p_Immunity_Time)
		{
			p_Immunity = false;
		}

	return true;
}

void Player::PlayerMovement()
{
	//Buttons Pressed
	bool RightPressed = false;
	bool LeftPressed = false;
	LookingUp = false;
	bool PressedJump = false;
	bool SprintPressed = false;

	if (controllerData.isAttached)
	{
		int leftstickX = controllerData.analogueButtons[2];
		int leftstickY = controllerData.analogueButtons[3];

		if (leftstickX > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			RightPressed = true;
		}

		if (leftstickX < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			LeftPressed = true;
		}

		if (leftstickY > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			LookingUp = true;
		}

		if (controllerData.digitalButtons[HK_DIGITAL_A])
		{
			PressedJump = true;
		}

		if (controllerData.digitalButtons[HK_DIGITAL_LEFT_THUMB])
		{
			SprintPressed = true;
		}
	}

	if (keyData.scanCode['W'])
		LookingUp = true;

	//SPRINTING
	//Checks whether the Left Shift key is being pressed. If its unlocked, If it is and the Player is not in the middle of falling or jumping, change the speed;
	if (upgrade_SPRINT)
	{
		if (keyData.scanCode[HK_LSHIFT])
			SprintPressed = true;

		if (SprintPressed && !p_isFalling && !p_isJumping)
		{
			if (upgrade_SUPER_JUMP)
			{
				p_jumpspeed = p_superjumpspeed;
			}
			p_isSprinting = true;
			p_speed = 4;
		}
		if (!SprintPressed && !p_isFalling && !p_isJumping)
			p_isSprinting = false;

		if (!p_isSprinting)
		{
			p_speed = 2;
			if (upgrade_SUPER_JUMP)
			{
				p_jumpspeed = p_normaljumpspeed;
			}
		}
	}


	//FORCE DOWN
	if (!p_isJumping && !p_groundunder)
	{
		setY(getY() + p_jumpspeed);
	}

	//MOVE PLAYER
	bool p_isMoving = false;

	if (keyData.scanCode['A'])
		LeftPressed = true;

	if (LeftPressed)
	{
		p_isMoving = true;
		p_isLeft = true;
		p_isRight = false;
		//ANIMATION
		
		if (!p_isJumping && !p_isFalling)
		{
			if (LookingUp)
				pSprite = pAnim_LeftUpRun;
			else
			{
				if (!p_isSprinting)
					pSprite = pAnim_LeftRun;
				else
					pSprite = pAnim_LeftSprint;
			}
		}
		if (p_isJumping)
		{
			pSprite = pAnim_LeftJump;
		}
		if (p_isFalling && !p_isJumping)
		{
			pSprite = pSprite_LeftFall;
		}
		
		if (!p_leftCol)
		{
			setX(getX() - p_speed);
		}
		if (getX() < 0)
		{
			setX(0);
		}


	}



	if (keyData.scanCode['D'])
		RightPressed = true;

	if (RightPressed)
	{
		p_isMoving = true;
		p_isLeft = false;
		p_isRight = true;
		//ANIMATIoN
		
		if (!p_isJumping)
		{
			if (LookingUp)
				pSprite = pAnim_RightUpRun;
			else
			{
				if (!p_isSprinting)
					pSprite = pAnim_RightRun;
				else
					pSprite = pAnim_RightSprint;
			}
		}
		if (p_isJumping)
		{
			pSprite = pAnim_RightJump;
		}
		if (p_isFalling && !p_isJumping)
		{
			pSprite = pSprite_RightFall;
		}
		
		if (!p_rightCol)
		{
			setX(getX() + p_speed);
		}
	}

		if (!LeftPressed && p_isLeft && !p_isJumping)
		{
			if (LookingUp)
				pSprite = pSprite_LeftUpIdle;
			else
				pSprite = pSprite_LeftIdle;
		}

		if (!RightPressed  && p_isRight && !p_isJumping)
		{
			if (LookingUp)
				pSprite = pSprite_RightUpIdle;
			else
				pSprite = pSprite_RightIdle;
		}
	

	if (p_isFalling && !p_isJumping)
	{
		if (p_isLeft)
		{
			pSprite = pSprite_LeftFall;
		}
		if (p_isRight)
		{
			pSprite = pSprite_RightFall;
		}
	}
	if (!p_isFalling && !p_isJumping && !p_isMoving)
	{
		if (p_isLeft)
		{
			if (LookingUp)
				pSprite = pSprite_LeftUpIdle;
			else
				pSprite = pSprite_LeftIdle;
		}
			
		if (p_isRight)
		{
			if (LookingUp)
				pSprite = pSprite_RightUpIdle;
			else
				pSprite = pSprite_RightIdle;
		}
	}

	if (keyData.scanCode[HK_SPACE])
		PressedJump = true;

	if(PressedJump)
	{
		if (!p_isJumping && !p_isFalling)
		{
			if (p_isLeft)
			{
				pSprite = pAnim_LeftJump;
			}
			if (p_isRight)
			{
				pSprite = pAnim_RightJump;
			}
			if (!p_isLeft && !p_isRight)
			{
				pSprite = pAnim_RightJump;
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

	setTexture(pSprite);
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

}

void Player::PlayerUpdate()
{
	gameClock = HAPI.GetTime();
	PlayerMovement();

}

bool Player::PlayerShoot(std::vector<Bullet*> bullets)
{

	if (controllerData.digitalButtons[HK_DIGITAL_X] || keyData.scanCode['N'])
	{
		if (!p_isShooting)
		{
			p_isShooting = true;
			p_shootingtime = gameClock + p_shootingdelay;

		}

		if (p_isShooting)
		{
			if (gameClock > p_shootingtime)
			{
				p_isShooting = false;

				if (LookingUp)
				{
					if (checkXRAYUpgrade())
					{
						Sound::playSound("Shoot 2");
						bullets.front()->setX(getX() + 13);
						bullets.front()->setY(getY());
						bullets.front()->fire("Up");
					}
					else
					{
						Sound::playSound("Shoot 1");
						bullets.front()->setX(getX() + 13);
						bullets.front()->setY(getY());
						bullets.front()->fire("Up");
					}
				}

				else if (FacingLeft())
				{
					if (checkXRAYUpgrade())
					{
						Sound::playSound("Shoot 2");
						bullets.front()->setX(getX());
						bullets.front()->setY(getY() + 10);
						bullets.front()->fire("Left");
					}
					else
					{
						Sound::playSound("Shoot 1");
						bullets.front()->setX(getX());
						bullets.front()->setY(getY() + 10);
						bullets.front()->fire("Left");
					}
				}
				else if (FacingRight())
				{
					if (checkXRAYUpgrade())
					{
						Sound::playSound("Shoot 2");
						bullets.front()->setX(getX() + 48);
						bullets.front()->setY(getY() + 10);
						bullets.front()->fire("Right");
					}
					else
					{
						Sound::playSound("Shoot 1");
						bullets.front()->setX(getX() + 48);
						bullets.front()->setY(getY() + 10);
						bullets.front()->fire("Right");
					}
				}
				return true;
			}
		}
	}
	return false;
}

void Player::MakeAnims()
{
}

void Player::checkHit(std::vector<Bullet*> b, int dmg)
{

	for (auto bullet : b)
	{

		if (bullet->checkActive())
		{
			Rectangle bulletRect = Rectangle(bullet->getTexture()->getWidth(), bullet->getTexture()->getHeight());
			bulletRect.Translate(bullet->getX(), bullet->getY());
			if (CollisionDetection::CheckCollision(player3, bulletRect))
			{
				AttackedUC(dmg);
				bullet->Destroy();
			}
		}
	}
}

void Player::Attacked(int damage)
{
	if (!PlayerImmunityCheck())
	{
		p_HP_cur -= damage;
		if (p_HP_cur > 0)
		{
			Sound::playSound("Damaged 1");
		}
		else
		{
			p_HP_cur = 0;
			Sound::playSound("Death");
			p_isAlive = false;

		}
	}
}

void Player::AttackedUC(int damage)
{
	p_HP_cur -= damage;
	if (p_HP_cur > 0)
	{
		Sound::playSound("Damaged 1");
	}
	else
	{
		p_HP_cur = 0;
		Sound::playSound("Death");
		p_isAlive = false;

	}
}

