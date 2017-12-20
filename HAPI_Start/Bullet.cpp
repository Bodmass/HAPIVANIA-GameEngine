#include "Bullet.h"

void Bullet::Update()
{
	BulletRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
	BulletRect.Translate(getX(), getY());

	if (isRight_)
		setX(getX() + bulletspeed);
	else
		setX(getX() - bulletspeed);
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
	isActive = false;
	bulletspeed = 0;
	this->setX(-100);
	this->setY(-100);
}

void Bullet::fire(bool isRight)
{
	isActive = true;
	isRight_ = isRight;
	bulletspeed = 7;
}

Bullet::~Bullet()
{
}
