#pragma once
#include "Texture.h"
#include "Rectangle.h"

class GameObject
{
protected:
	Texture* texture_ = nullptr;
	Rectangle rectangle_;
	int positionX{ 0 }, positionY{ 0 };

public:
	GameObject();
	GameObject(Texture* texture, Rectangle rectangle, int posX, int posY, bool isBG = false);
	virtual Texture* getTexture() { return texture_; }
	virtual Rectangle getRect() { return rectangle_; }
	virtual int getX() { return positionX; }
	virtual int getY() { return positionY; }
	virtual void setX(int x) { positionX = x; }
	virtual void setY(int y) { positionY = y; }
	virtual void setTexture(Texture* texture);
	virtual void setRectangle(Rectangle rectangle) { rectangle_ = rectangle; }
	virtual ~GameObject();
};

