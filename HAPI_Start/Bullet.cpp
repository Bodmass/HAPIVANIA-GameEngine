#include "Bullet.h"


void Bullet::Update()
{
	if (isRight_)
		setX(getX() + bulletspeed);
	else
		setX(getX() - bulletspeed);
}

Bullet::~Bullet()
{
}
