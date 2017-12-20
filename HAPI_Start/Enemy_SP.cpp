#include "Enemy_SP.h"


Enemy_SP::~Enemy_SP()
{
}

void Enemy_SP::Update(Player * plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{

	if (state == State::Idle)
	{
		float angle = AngleToTarget(getX(), getY(), plyr->getX(), plyr->getY());
		if (plyr->getX() < getX())
			setTexture(pSprite_LeftIdle);
		else
			setTexture(pSprite_RightIdle);
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

		if (plyr->getX() < getX())
			setTexture(pAnim_LeftRun);
		else
			setTexture(pAnim_RightRun);

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

			if (angle > 0)
				setTexture(pAnim_LeftRun);
			else
				setTexture(pAnim_RightRun);

			if (threshold / 4 > CheckDistance(getX(), getY(), plyr->getX(), plyr->getY()))
			{
				state = State::Follow;
			}
		}
	}
}
