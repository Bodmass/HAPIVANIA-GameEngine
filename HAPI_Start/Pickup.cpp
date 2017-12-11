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
			plyr->setSprintUpgrade();
			Sound::playSound("Upgrade");
			Destroy();
		}
	}
}

void Pickup::Destroy()
{
	//Temp (Ceejay laughed at me for making this, am sad)
	this->setX(-100);
	this->setY(-100);
}
