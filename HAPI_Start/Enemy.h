#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	~Enemy();
};

