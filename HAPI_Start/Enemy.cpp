#include "Enemy.h"
#include "Sound.h"


Enemy::~Enemy()
{
}

void Enemy::checkHit(std::vector<Bullet*> b)
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

void Enemy::isHit(int amount)
{
	e_HP -= amount;

	if (e_HP <= 0)
	{
		Sound::playSound("Enemy Death");
		Kill();
	}
	else
		Sound::playSound("Enemy Damaged 1");




	


}

void Enemy::Kill()
{
	e_isAlive = false;
	setX(-100);
	setY(-100);
}

void Enemy::Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{
	if (e_isAlive)
	{
		if (state == State::Idle)
		{

			//std::cout << "I'm Idle, and you're " << CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()) << " pixels from me." << std::endl;
			if (threshold >= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
			{
				state = State::Follow;
			}
		}

		else if (state == State::Follow)
		{
			//std::cout << "I'm Following" << std::endl;
			float angle = AngleToTarget(getX(), getY(), plyr->getX(), plyr->getY());

			//if (threshold < CheckDistance(getX(), getY(), plyr->getX(), plyr->getY()))
				//state = State::Return;

			if (!ReachedEnd(platforms, camRect))
			{

				if (attack_range <= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
					setX(getX() + (2 * cos(angle)));

			}
			else
			{
				state = State::Return;
			}

			if (attack_range >= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
			{
				int e_Damage = rand() % (e_Damage_Max - e_Damage_Min + 1) + e_Damage_Min;
				plyr->Attacked(e_Damage);
			}
		}

		else if (state == State::Return)
		{
			if (5 >= CheckDistance(getX(), getY(), origin_x, origin_y))
			{
				setX(origin_x);
				state = State::Idle;
			}
			else
			{
				float angle = AngleToTarget(getX(), getY(), origin_x, origin_y);
				setX(getX() + (2 * cos(angle)));

				if (threshold / 4 > CheckDistance(getX(), getY(), plyr->getX(), plyr->getY()))
				{
					state = State::Follow;
				}
			}
		}
	}
}

float Enemy::CheckDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));
}

float Enemy::AngleToTarget(int x1, int y1, int x2, int y2)
{
	float deltaX = (x2 - x1);
	float deltaY = (y2 - y1);
	return atan2(deltaY, deltaX);
}

bool Enemy::ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect)
{
	Rectangle enemyfeetLeft = Rectangle(2, 4);
	Rectangle enemyfeetRight = Rectangle(2, 4);

	enemyfeetLeft.Translate(getX() - 2, getY() + 44);
	enemyfeetRight.Translate(getX() + this->getTexture()->getWidth() + 2, getY() + 44);

	bool leftdown{ false };
	bool rightdown{ false };

	for (int i = 0; i < platforms.size(); i++)
	{
		if (camRect.rOutside(platforms[i]))
		{
			if (CollisionDetection::CheckCollision(enemyfeetLeft, platforms[i]))
			{
				std::cout << "Left Down\n";
				leftdown = true;
			}
			if (CollisionDetection::CheckCollision(enemyfeetRight, platforms[i]))
			{
				rightdown = true;
				std::cout << "Right Down\n";
			}
		}
	}

	if (leftdown&&rightdown)
	{
		return false;
	}


	return true;
}
