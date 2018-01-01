#include "Bullet.h"

void Bullet::Update(int pX, int pY)
{
	BulletRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
	BulletRect.Translate(getX(), getY());

	//Change Bullet Direction on Update depending on the Direction set.
	if (dir == Facing::Right)
		setX(getX() + bulletspeed);
	else if (dir == Facing::Left)
		setX(getX() - bulletspeed);
	else if (dir == Facing::Up)
		setY(getY() - bulletspeed);
	else if (dir == Facing::Down)
		setY(getY() + bulletspeed);
	else if (dir == Facing::Homing)
	{
		float deltaX = (float)(getX() - pX);
		float deltaY = (float)(getY() - pY);
		float delta = atan2(deltaY, deltaX);

		setX(getX() + (int)(-5.25 * cos(delta)));
		setY(getY() + bulletspeed);
	};
}

void Bullet::CheckCollision(std::vector<Rectangle> platforms)
{
	
	//Check if the bullet has hit a platform

	for (auto col : platforms)
	{
		int Distance = abs(col.getLeft() - BulletRect.getLeft());

		if (Distance <= 60)
		{
			if (CollisionDetection::CheckCollision(col, BulletRect))
			{
				Destroy();
			}
		}
	}
}



void Bullet::Destroy()
{
	//Deactivate the Bullet and Hide it off Screen
	isActive = false;
	bulletspeed = 0;
	this->setX(-100);
	this->setY(-100);
}

void Bullet::fire(std::string face)
{
	isActive = true;
	bulletspeed = 7;
	isUp = false;
	if (face == "Right" || face == "right")
		dir = Facing::Right;
	else if (face == "Left" || face == "left")
		dir = Facing::Left;
	else if (face == "Up" || face == "up")
	{
		isUp = true;
		dir = Facing::Up;
	}
	else if (face == "Down" || face == "down")
	{
		isUp = true;
		dir = Facing::Down;
	}
	else if (face == "Homing" || face == "homing")
	{
		isUp = true;
		dir = Facing::Homing;
	}

}

Bullet::~Bullet()
{
}
