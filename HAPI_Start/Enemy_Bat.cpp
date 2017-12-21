#include "Enemy_Bat.h"

Enemy_Bat::~Enemy_Bat()
{
}


void Enemy_Bat::Update(Player * plyr, std::vector<Rectangle> platforms, Rectangle camRect)
{
	if (e_isAlive)
	{
		gameClock = HAPI.GetTime();
		if (state == State::Idle)
		{
			attackClock = gameClock + 600;
			float angle = AngleToTarget(getX(), getY(), plyr->getX(), plyr->getY());
			setTexture(pSprite_Idle);
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
			{
				setTexture(pAnim_LeftRun);
			}
			else
			{
				setTexture(pAnim_RightRun);
			}

			if (threshold < CheckDistance(getX(), getY(), plyr->getX(), plyr->getY()))
				state = State::Return;

			if (attack_range <= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
			{

				//std::cout <<(origin_x - getX()) << std::endl;
				//std::cout << "Speed: " << (2 * cos(angle)) << std::endl;
				setY(getY() + (e_Speed * sin(angle)));
				setX(getX() + (e_Speed * cos(angle)));
				if (attack_range >= CheckDistance(plyr->getX(), plyr->getY(), getX(), getY()))
				{
					int e_Damage = rand() % (e_Damage_Max - e_Damage_Min + 1) + e_Damage_Min;
					plyr->Attacked(e_Damage);
					state = State::Return;
				}

			}

			else
			{
				state = State::Return;
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
				setY(getY() + (e_Speed * sin(angle)));
				setX(getX() + (e_Speed * cos(angle)));

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
}

bool Enemy_Bat::ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect)
{
	return false;
}

void Enemy_Bat::BatConflict(Enemy* enemies)
{
	if (dynamic_cast<Enemy_Bat*>(enemies))
	{
		Rectangle thisbat = Rectangle(2, this->getTexture()->getHeight());
		Rectangle thatbat = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());

		thisbat.Translate(getX() + this->getTexture()->getWidth() , getY());
		thatbat.Translate(enemies->getX(), enemies->getY());
		if (CollisionDetection::CheckCollision(thisbat, thatbat))
		{
			e_Speed = 2.3;
			return;
		}

		e_Speed = 2.3;
		return;
	}
	return;
}
