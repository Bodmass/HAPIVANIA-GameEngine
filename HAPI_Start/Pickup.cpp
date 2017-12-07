#include "Pickup.h"
#include "CollisionDetection.h"

Pickup::~Pickup()
{
}

void Pickup::Update(Player* plyr)
{
	if (CollisionDetection::CheckCollision(this->getRect() , plyr->getRect()))
	{
		Collected = true;
	}

	if (Collected)
	{
		if (p_ID == 1) //SPRINT
		{
			plyr->setSprintUpgrade();
		}
	}
}
