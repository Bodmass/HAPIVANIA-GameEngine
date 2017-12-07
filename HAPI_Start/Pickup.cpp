#include "Pickup.h"
#include "CollisionDetection.h"

Pickup::~Pickup()
{
}

void Pickup::Update(Rectangle plyr)
{
	setRectangle(Rectangle(getTexture()->getWidth(), getTexture()->getHeight()));
	getRect().Translate(getX(), getY());

	if (CollisionDetection::CheckCollision(getRect(), plyr))
	{
		std::cout << "Picked Up" << std::endl;
	}
}

void Pickup::Destroy()
{

}
