#include "Boss.h"


Boss::~Boss()
{
}

void Boss::Update(Player * plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{
	gameClock = HAPI.GetTime();

	if (!isSetup)
	{
		isSetup = true;
		phase = Phase::Phase1;
		dir = Direction::Right;
		setTexture(pSprite_Idle);
	}
	
	if (isActive)
	{
		if (getX() >= 1900 - getTexture()->getWidth())
			dir = Direction::Left;
		if (getX() <= 1100)
			dir = Direction::Right;

		if (e_HP < 1750 && e_HP > 500)
			phase = Phase::Phase2;
		if (e_HP < 750 && e_HP > 1)
			phase = Phase::Phase3;

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
					isHit(20);
					bullet->Destroy();
				}
			}
		}
	}
}

bool Boss::Shoot()
{
	if (isActive)
	{
		if (phase == Phase::Phase1)
		{
			if (gameClock > attackClock)
			{
				attackClock = gameClock + 500;

				//

				//

				return true;
			}
		}

		else if (phase == Phase::Phase2)
		{
			if (gameClock > attackClock)
			{
				attackClock = gameClock + 250;

				//

				//

				return true;
			}
		}

		else if (phase == Phase::Phase3)
		{
			if (gameClock > attackClock)
			{
				attackClock = gameClock + 150;

				//

				//

				return true;
			}
		}
		
		/*
		if (phase == Phase::Phase1)
		{
			if (b->getX() < 100)
			{
				b->setX(getX() + this->getTexture()->getWidth() / 2);
				b->setY(getY() + this->getTexture()->getHeight());
			}

			if (b->getY() > 650)
			{
				float deltaX = (b->getX() - pX);
				float deltaY = (b->getY() - pY);
				float delta = atan2(deltaY, deltaX);

				b->setX(b->getX() + (5 * cos(delta)));
				b->setY(b->getY() + (5 * sin(delta)));
				
				
			}
			else
			{
				b->setX(getX() + this->getTexture()->getWidth() / 2);
				b->setY(getY() + this->getTexture()->getHeight());
			}
		}
		*/
	}
	
	return false;
}

void Boss::Activate()
{
	e_HP = 2500;
	isActive = true;
}

bool Boss::ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect)
{
	return false;
}
