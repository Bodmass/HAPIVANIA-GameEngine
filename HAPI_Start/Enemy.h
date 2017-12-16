#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
private:
	int e_HP{ 100 };
	int e_Damage{ 10 };
	bool e_isAlive{ true };

public:
	Enemy(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	~Enemy();
	void Kill() { e_isAlive = false; }
};

