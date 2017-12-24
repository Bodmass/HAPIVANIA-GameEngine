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

	for (int i = 0; i < platforms.size(); i++)
	{
		if (camRect.rOutside(platforms[i]))
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
		if (camRect.rOutside(platforms[i]))
		{
			if (CollisionDetection::CheckCollision(playerright, platforms[i]))
			{
				p_rightCol = true;
				break;
			}
		}


	}

	for (int i = 0; i < platforms.size(); i++)
	{
		if (camRect.rOutside(platforms[i]))
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
		if (camRect.rOutside(platforms[i]))
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
	if (keyData.scanCode[HK_NUMPAD1])
	{
		upgrade_SPRINT = true;
	}

	if (keyData.scanCode[HK_NUMPAD2])
	{
		upgrade_SUPER_JUMP = true;
	}
	//SPRINTING
	//Checks whether the Left Shift key is being pressed. If its unlocked, If it is and the Player is not in the middle of falling or jumping, change the speed;
	if (upgrade_SPRINT)
	{
		if (keyData.scanCode[HK_LSHIFT] && !p_isFalling && !p_isJumping)
		{
			if (upgrade_SUPER_JUMP)
			{
				p_jumpspeed = p_superjumpspeed;
			}
			p_isSprinting = true;
			p_speed = 4;
		}
		if (!keyData.scanCode[HK_LSHIFT] && !p_isFalling && !p_isJumping)
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
		
		if (!p_isJumping && !p_isFalling)
		{
			if (!p_isSprinting)
				pSprite = pAnim_LeftRun;
			else
				pSprite = pAnim_LeftSprint;
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
	{
		p_isMoving = true;
		p_isLeft = false;
		p_isRight = true;
		//ANIMATIoN
		
		if (!p_isJumping)
		{
			if (!p_isSprinting)
				pSprite = pAnim_RightRun;
			else
				pSprite = pAnim_RightSprint;
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

		if (!keyData.scanCode['A'] && p_isLeft && !p_isJumping)
		{
			pSprite = pSprite_LeftIdle;
		}

		if (!keyData.scanCode['D']  && p_isRight && !p_isJumping)
		{
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
			pSprite = pSprite_LeftIdle;
		}
			
		if (p_isRight)
		{
			pSprite = pSprite_RightIdle;
		}
	}

	if (keyData.scanCode[HK_SPACE])
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
	if (keyData.scanCode['n'] || keyData.scanCode['N'])
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
				//std::cout << "I've shot!\n";
				p_isShooting = false;

				if (keyData.scanCode['w'] || keyData.scanCode['W'])
				{
					if (checkXRAYUpgrade())
					{
						Sound::playSound("Shoot 2");
						bullets.front()->setX(getX() + 13);
						bullets.front()->setY(getY());
						//bulletObjects.front()->setTexture(game_->getGraphics().getSprite("Player_Bullet_2"));
						bullets.front()->fire("Up");
						//std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
					}
					else
					{
						Sound::playSound("Shoot 1");
						bullets.front()->setX(getX() + 13);
						bullets.front()->setY(getY());
						//bulletObjects.front()->setTexture(game_->getGraphics().getSprite("Player_Bullet_1"));
						bullets.front()->fire("Up");
						//std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
					}
				}

				else if (FacingLeft())
				{
					if (checkXRAYUpgrade())
					{
						Sound::playSound("Shoot 2");
						bullets.front()->setX(getX());
						bullets.front()->setY(getY() + 10);
						//bulletObjects.front()->setTexture(game_->getGraphics().getSprite("Player_Bullet_2"));
						bullets.front()->fire("Left");
						//std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
					}
					else
					{
						Sound::playSound("Shoot 1");
						bullets.front()->setX(getX());
						bullets.front()->setY(getY() + 10);
						//bulletObjects.front()->setTexture(game_->getGraphics().getSprite("Player_Bullet_1"));
						bullets.front()->fire("Left");
						//std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
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
						//std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
					}
					else
					{
						Sound::playSound("Shoot 1");
						bullets.front()->setX(getX() + 48);
						bullets.front()->setY(getY() + 10);
						//bulletObjects.front()->setTexture(game_->getGraphics().getSprite("Player_Bullet_1"));
						bullets.front()->fire("Right");
						//std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
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

