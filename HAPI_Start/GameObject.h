#pragma once
#include "Texture.h"
#include "Rectangle.h"

class GameObject
{
private:
	Texture* texture_ = nullptr;
	Rectangle rectangle_;
	int positionX{ 0 }, positionY{ 0 };

public:
	GameObject();
	GameObject(Texture* texture, Rectangle rectangle, int posX, int posY, bool isBG = false);
	Texture* getTexture() { return texture_; }
	Rectangle getRect() { return rectangle_; }
	int getX() { return positionX; }
	int getY() { return positionY; }
	void setX(int x) { positionX = x; }
	void setY(int y) { positionY = y; }
	~GameObject();
};

