#include "rectangle.h"
#include <algorithm>

void Rectangle::Translate(int x, int y)
{
	rLeft += x;
	rRight += x;
	rTop += y;
	rBtm += y;
}

void Rectangle::Move(int x, int y)
{
	rPosX = x;
	rPosY = y;
}

int Rectangle::Clamp(int number, int lowest, int highest)
{
	return std::min(highest, std::max(number, lowest));
}

Rectangle Rectangle::rContains(Rectangle & rect)
{
	Rectangle clippedRect;

	clippedRect.setLeft(Clamp(rect.getLeft(), getLeft(), getRight()));
	clippedRect.setRight(Clamp(rect.getRight(), getLeft(), getRight()));
	clippedRect.setTop(Clamp(rect.getTop(), getTop(), getBtm()));
	clippedRect.setBtm(Clamp(rect.getBtm(), getTop(), getBtm()));

	return clippedRect;
}

bool Rectangle::rOutside(Rectangle & rect)
{
	//Rectangle contains = rContains(rect);
	if (getRight() > rect.getLeft())
	{
		return true;
	}

	if (getBtm() < rect.getTop())
	{
		return true;
	}

	if (getLeft() > rect.getRight())
	{
		return true;
	}

	if (getTop() > rect.getBtm())
	{
		return true;
	}

	return false;
}
