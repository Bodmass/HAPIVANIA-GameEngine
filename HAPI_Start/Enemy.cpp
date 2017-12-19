#include "Enemy.h"


Enemy::~Enemy()
{
}

void Enemy::Update(Player* plyr)
{
	if (state == State::Idle)
	{
		//std::cout << "I'm Idle, and you're " << CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()) << " pixels from me." << std::endl;
		if (threshold >= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
		{
			state = State::Follow;
		}
	}

	if (state == State::Follow)
	{
		//std::cout << "I'm Following" << std::endl;
		if (attack_range >= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
		{
			plyr->Attacked(e_Damage);
		}
	}

	if (state == State::Return)
	{
		//std::cout << "I'm Returning" << std::endl;
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
