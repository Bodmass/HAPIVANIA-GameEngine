#include "CollisionDetection.h"
#include <iostream>


CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

bool CollisionDetection::CheckCollision(Rectangle player, Rectangle object)
{
	std::cout << "The player is at: " << player.getTop() << " and the Object is at " << object.getTop() << std::endl;
	std::cout << "Checking for Collision: ";
	if ((player.getX() >= object.getX() && player.getX() <= (object.getX() + object.getWidth())) ||
		(player.getX() + player.getWidth()) >= object.getX() && (player.getX() + player.getWidth()) <= (object.getX() + object.getWidth()))
	{
		std::cout << "X Collsion ";
		if ((player.getY() >= object.getY() && player.getY() <= (object.getY() + object.getHeight())) ||
			(player.getY() + player.getHeight()) >= object.getY() && (player.getY() + player.getHeight()) <= (object.getY() + object.getHeight()))
		{
			std::cout << " and Y Collision!" << std::endl;
			return true;
		}
		std::cout << "only!" << std::endl;
	}
	std::cout << "Nothing at all" << std::endl;
	return false;
}
