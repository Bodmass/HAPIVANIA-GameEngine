#include "Pickup.h"
#include "Sound.h"

Pickup::~Pickup()
{
}

void Pickup::Update(Player* plyr)
{
	if (!Collected)
	{

		PickupRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
		PickupRect.Translate(getX(), getY());

		if (CollisionDetection::CheckCollision(plyr->getPlayerRect(), PickupRect))
		{
			PickedUp(plyr);
		}
	}
}

void Pickup::PickedUp(Player* plyr)
{
	std::cout << "Something Picked Up" << std::endl;
	Collected = true;
	if (p_ID == 0)
	{
		//HEALTH
	}
	if (p_ID == 1)
	{
		plyr->setSprintUpgrade();
		Sound::playSound("Upgrade");
	}
	if (p_ID == 2)
	{
		plyr->setJumpUpgrade();
		Sound::playSound("Upgrade");
	}
	if (p_ID == 3)
	{
		plyr->setXRAYUpgrade();
		Sound::playSound("Upgrade");
	}
	Destroy();
}

void Pickup::Destroy()
{
	//Temp (Ceejay laughed at me for making this, am sad)
	this->setX(-100);
	this->setY(-100);
}
