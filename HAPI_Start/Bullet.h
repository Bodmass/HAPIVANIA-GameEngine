#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	bool isRight_{ false };
	int bulletspeed = 5;
public:
	Bullet(bool isRight, Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) { isRight_ = isRight; };
	void Update();
	~Bullet();
};

