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

			int Distance = abs(bulletRect.getLeft() - enemyRect.getLeft());

			if (Distance <= 60)
			{
				if (CollisionDetection::CheckCollision(enemyRect, bulletRect))
				{
					isHit(bullet->getDamage());
					bullet->Destroy();
				}
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
	setX(-1000);
	setY(-1000);
}

void Enemy::Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{
	if (e_isAlive)
	{
		if (state == State::Idle)
		{

			//Get the Distance and if within the Threshold, start following
			if (threshold >= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
			{
				state = State::Follow;
			}
		}

		else if (state == State::Follow)
		{
			//Get the Angle between the this and the Player
			float angle = AngleToTarget(getX(), getY(), plyr->getX(), plyr->getY());

			
			//If the enemy isnt off the side of a platform keep following, else Return to Origin
			if (!ReachedEnd(platforms, camRect))
			{
				//Keep following until the distance left between the enemy and player is the attack range
				if (attack_range <= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
					setX(getX() + (int)(2 * cos(angle)));

			}
			else
			{
				state = State::Return;
			}

			//If inside the attack range, deal damage
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
				setX(getX() + (int)(2 * cos(angle)));

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
	float deltaX = (float)(x2 - x1);
	float deltaY = (float)(y2 - y1);
	return atan2(deltaY, deltaX);
}

bool Enemy::ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect)
{
	Rectangle enemyfeetLeft = Rectangle(2, 4);
	Rectangle enemyfeetRight = Rectangle(2, 4);
	Rectangle enemyfeet = Rectangle(this->getTexture()->getWidth(), 4);

	enemyfeetLeft.Translate(getX() - 2, getY() + 44);
	enemyfeetRight.Translate(getX() + this->getTexture()->getWidth() + 2, getY() + 44);
	enemyfeet.Translate(getX(), getY() + 44);

	bool leftdown{ false };
	bool rightdown{ false };

	for (int i = 0; i < platforms.size(); i++)
	{

		int Distance = abs(platforms[i].getLeft() - enemyfeet.getLeft());

		if (Distance <= 60)
		{
			if (CollisionDetection::CheckCollision(enemyfeetLeft, platforms[i]))
			{
				leftdown = true;
			}
			if (CollisionDetection::CheckCollision(enemyfeetRight, platforms[i]))
			{
				rightdown = true;
			}
		}
	}

	if (leftdown&&rightdown)
	{
		return false;
	}


	return true;
}

void Enemy::Setup()
{

}
