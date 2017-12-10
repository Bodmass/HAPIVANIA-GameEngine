#include "Pickup.h"
#include "CollisionDetection.h"

Pickup::~Pickup()
{
}

void Pickup::Update(Player* plyr)
{
	if (!Collected)
	{
		PickupRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
		PickupRect.Translate(getX(), getY());

		//setRectangle(Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight()));
		//getRect().setLeft(getX());
		//getRect().setTop(getY());

		//std::cout << "Player: " << plyr.getLeft() <<  ", " << plyr.getTop() << std::endl;
		//std::cout << "Pickup: " << PickupRect.getLeft() << ", " << PickupRect.getTop() << std::endl;

		if (CollisionDetection::CheckCollision(plyr->getPlayerRect(), PickupRect))
		{
			plyr->setSprintUpgrade();
			HAPI.PlayStreamedMedia("Audio/SE/ItemRecieved.mp3");
			//std::cout << "Picked Up" << std::endl;
			Destroy();
		}
	}
}

void Pickup::Destroy()
{
	this->setX(-100);
	this->setY(-100);
}
