#include "Bullet.h"

void Bullet::Update()
{
	BulletRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
	BulletRect.Translate(getX(), getY());

	if (dir == Facing::Right)
		setX(getX() + bulletspeed);
	else if (dir == Facing::Left)
		setX(getX() - bulletspeed);
	else if (dir == Facing::Up)
		setY(getY() - bulletspeed);
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

void Bullet::fire(std::string face)
{
	if (face == "Right" || face == "right")
		dir = Facing::Right;
	else if (face == "Left" || face == "left")
		dir = Facing::Left;
	else if (face == "Up" || face == "up")
		dir = Facing::Up;

	isActive = true;
	bulletspeed = 7;
}

Bullet::~Bullet()
{
}
