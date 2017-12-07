#pragma once 

#include "Rectangle.h"
#include <iostream>


class CollisionDetection
{
private:

public:
	static bool CollisionDetection::CheckCollision(Rectangle player, Rectangle object)
	{
		Rectangle contains = object.rContains(player);
		if (contains.getWidth() <= 0 || contains.getHeight() <= 0)
		{
			return false;
		}
		//std::cout << player.getLeft() << ", " << player.getTop() << ", " << player.getRight() << ", " << player.getBtm() << std::endl;
		return true;

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

