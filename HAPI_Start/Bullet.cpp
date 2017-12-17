#include "Bullet.h"


void Bullet::Update()
{
	if (isRight_)
		setX(getX() + bulletspeed);
	else
		setX(getX() - bulletspeed);

	BulletRect.Translate(getX(), getY());
}

void Bullet::CheckCollision(std::vector<Rectangle> platforms)
{
	
	//BulletRect.Translate(getX(), getY());

	for (auto col : platforms)
	{
		if (CollisionDetection::CheckCollision(col, BulletRect))
		{
			Destroy();
		}
	}
}

void Bullet::Destroy()
{
	//TEMP
	bulletspeed = 0;
	this->setX(-100);
	this->setY(-100);
	BulletRect.Translate(getX(), getY());
}

void Bullet::fire(bool isRight)
{
	isRight_ = isRight;
	bulletspeed = 7;
}

Bullet::~Bullet()
{
}
