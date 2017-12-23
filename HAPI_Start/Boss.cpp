#include "Boss.h"


Boss::~Boss()
{
}

void Boss::Update(Player * plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{

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

		if (phase == Phase::Phase1)
		{
			if (dir == Direction::Right)
				setX(getX() + 1);
			else if (dir == Direction::Left)
				setX(getX() - 1);
		}
		else if (phase == Phase::Phase2)
		{

		}
		else if (phase == Phase::Phase3)
		{

		}
	}
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
