#include "Boss.h"


Boss::~Boss()
{
}

void Boss::Update(Player * plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{
	gameClock = HAPI.GetTime();

	if (isActive)
	{

		//Move the Boss Left and Right
		if (getX() >= 1900 - getTexture()->getWidth())
			dir = Direction::Left;
		if (getX() <= 1100)
			dir = Direction::Right;

		if (e_HP < phase2HP && e_HP > phase3HP)
			phase = Phase::Phase2;
		if (e_HP < phase3HP && e_HP > 1)
			phase = Phase::Phase3;

		//Increase the Speed of the Ship per Phase
		if (phase == Phase::Phase1)
		{
			if (dir == Direction::Right)
				setX(getX() + 1);
			else if (dir == Direction::Left)
				setX(getX() - 1);
		}
		else if (phase == Phase::Phase2)
		{
			if (dir == Direction::Right)
				setX(getX() + 2);
			else if (dir == Direction::Left)
				setX(getX() - 2);
		}
		else if (phase == Phase::Phase3)
		{
			if (dir == Direction::Right)
				setX(getX() + 3);
			else if (dir == Direction::Left)
				setX(getX() - 3);
		}
	}
}

void Boss::checkHit(std::vector<Bullet*> b)
{
	if (isActive)
	{
		Rectangle enemyRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
		enemyRect.Translate(this->getX(), this->getY());

		for (auto bullet : b)
		{

			if (bullet->checkActive())
			{
				Rectangle bulletRect = Rectangle(bullet->getTexture()->getWidth(), bullet->getTexture()->getHeight());
				bulletRect.Translate(bullet->getX(), bullet->getY());
				if (CollisionDetection::CheckCollision(enemyRect, bulletRect))
				{
					isHit(bullet->getDamage());
					bullet->Destroy();
				}
			}
		}
	}
}

bool Boss::Shoot(std::vector<Bullet*> b, Player* plyr)
{
	if (isActive)
	{
		if (phase == Phase::Phase1)
		{
			if (gameClock > swapClock)
			{
				
				//Randomly Select a Move
				atk = static_cast<Moves>(rand() % Other);

				if (atk == DoubleBeam)
					swapClock = gameClock + 5000;
				if (atk == HomingMissile)
					swapClock = gameClock + 3500;
				if (atk == Other)
					swapClock = gameClock + 1500;
				
			}

			if (gameClock > attackClock)
			{

				if (atk == DoubleBeam)
				{
					attackClock = gameClock + 500;

					Sound::playSound("Shoot 2");
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) / 2);
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("down");
					std::rotate(b.begin(), b.begin() + 1, b.end());
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) + ((this->getTexture()->getWidth() / 2) / 2));
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("down");
				}
				else if (atk == HomingMissile)
				{
					attackClock = gameClock + 500;
					Sound::playSound("Shoot 2");
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) / 2);
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("homing");
					std::rotate(b.begin(), b.begin() + 1, b.end());
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) + ((this->getTexture()->getWidth() / 2) / 2));
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("homing");
				}
				else if (atk == Other)
				{
					//std::cout << "The Boss is shooting other things at you!\n";
				}
				return true;
			}
		}

		else if (phase == Phase::Phase2)
		{
			if (gameClock > swapClock)
			{

				//Randomly Select a Move
				atk = static_cast<Moves>(rand() % Other);

				if (atk == DoubleBeam)
					swapClock = gameClock + 5000;
				if (atk == HomingMissile)
					swapClock = gameClock + 3500;
				if (atk == Other)
					swapClock = gameClock + 1500;

			}

			if (gameClock > attackClock)
			{

				if (atk == DoubleBeam)
				{
					attackClock = gameClock + 250;

					Sound::playSound("Shoot 2");
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) / 2);
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("down");
					std::rotate(b.begin(), b.begin() + 1, b.end());
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) + ((this->getTexture()->getWidth() / 2) / 2));
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("down");
				}
				else if (atk == HomingMissile)
				{
					attackClock = gameClock + 250;
					Sound::playSound("Shoot 2");
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) / 2);
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("homing");
					std::rotate(b.begin(), b.begin() + 1, b.end());
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) + ((this->getTexture()->getWidth() / 2) / 2));
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("homing");
				}
				else if (atk == Other)
				{
					//std::cout << "The Boss is shooting other things at you!\n";
				}
				return true;
			}
		}

		else if (phase == Phase::Phase3)
		{
			if (gameClock > swapClock)
			{

				//Randomly Select a Move
				atk = static_cast<Moves>(rand() % Other);

				if (atk == DoubleBeam)
					swapClock = gameClock + 5000;
				if (atk == HomingMissile)
					swapClock = gameClock + 3500;
				if (atk == Other)
					swapClock = gameClock + 1500;

			}

			if (gameClock > attackClock)
			{

				if (atk == DoubleBeam)
				{
					attackClock = gameClock + 150;

					Sound::playSound("Shoot 2");
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) / 2);
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("down");
					std::rotate(b.begin(), b.begin() + 1, b.end());
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) + ((this->getTexture()->getWidth() / 2) / 2));
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("down");
				}
				else if (atk == HomingMissile)
				{
					attackClock = gameClock + 150;
					Sound::playSound("Shoot 2");
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) / 2);
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("homing");
					std::rotate(b.begin(), b.begin() + 1, b.end());
					b.front()->setX(this->getX() + (this->getTexture()->getWidth() / 2) + ((this->getTexture()->getWidth() / 2) / 2));
					b.front()->setY(this->getY() + this->getTexture()->getHeight());
					b.front()->fire("homing");

					//std::cout << "The Boss is shooting missiles at you!\n";
				}
				else if (atk == Other)
				{
					//Boss Break
				}
				return true;
			}
		}
		

	}
	
	return false;
}

void Boss::Activate()
{
	if (isHardMode)
	{
		e_Damage_Min = 10;
		e_Damage_Max = 20;
		e_HP = 2500;
		phase2HP = 1750;
		phase3HP = 750;
	}
	else
	{
		e_Damage_Min = 5;
		e_Damage_Max = 7;
		e_HP = 1250;
		phase2HP = 750;
		phase3HP = 250;
	}

	atk = Moves::DoubleBeam;
	swapClock = gameClock + 5000;
	isSetup = true;
	phase = Phase::Phase1;
	dir = Direction::Right;
	setTexture(pSprite_Idle);


	isActive = true;
}

bool Boss::ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect)
{
	return false;
}

void Boss::isHit(int amount)
{
	e_HP -= amount;

	if (e_HP <= 0)
	{
		Sound::playSound("Enemy Death");
		isDead = true;
		isActive = false;
	}
	else
		Sound::playSound("Enemy Damaged 1");

}

void Boss::Kill()
{
	e_isAlive = false;
	setX(-1000);
	setY(-1000);
}