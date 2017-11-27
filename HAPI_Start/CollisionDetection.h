#pragma once 

#include "Rectangle.h"
#include <iostream>


class CollisionDetection
{
private:

public:
	static bool CollisionDetection::CheckCollision(Rectangle player, Rectangle object)
	{
		//std::cout << "The player is at: " << player.getX() << "," << player.getY() << " and the Object is at " << object.getX() << "," << object.getY() << std::endl;
		//std::cout << "Checking for Collision: ";
		if ((player.getX() >= object.getX() && player.getX() <= (object.getX() + object.getWidth())) ||
			(player.getX() + player.getWidth()) >= object.getX() && (player.getX() + player.getWidth()) <= (object.getX() + object.getWidth()))
		{
			//std::cout << "X Collsion ";
			if ((player.getY() >= object.getY() && player.getY() <= (object.getY() + object.getHeight())) ||
				(player.getY() + player.getHeight()) >= object.getY() && (player.getY() + player.getHeight()) <= (object.getY() + object.getHeight()))
			{
				//std::cout << " and Y Collision!" << std::endl;
				return true;
			}
			//std::cout << "only!" << std::endl;
		}
		//std::cout << "Nothing at all" << std::endl;
		return false;
	}

	static bool CollisionDetection::CheckXCollision(Rectangle player, Rectangle object)
	{
		if ((player.getX() >= object.getX() && player.getX() <= (object.getX() + object.getWidth())) ||
			(player.getX() + player.getWidth()) >= object.getX() && (player.getX() + player.getWidth()) <= (object.getX() + object.getWidth()))
		{
				return true;
		}
		return false;
	}

	static bool CollisionDetection::CheckYCollision(Rectangle player, Rectangle object)
	{
		if ((player.getY() >= object.getY() && player.getY() <= (object.getY() + object.getHeight())) ||
			(player.getY() + player.getHeight()) >= object.getY() && (player.getY() + player.getHeight()) <= (object.getY() + object.getHeight()))
		{
			return true;
		}
		return false;
	}
	//void AABB(); //Axis-Aligned Bounding Boxes
	//void C2C(); //Circle to Circle
};

