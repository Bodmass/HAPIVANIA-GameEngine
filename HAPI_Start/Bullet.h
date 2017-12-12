#pragma once
#include "GameObject.h"
#include "CollisionDetection.h"

class Bullet : public GameObject
{
private:
	bool isRight_{ false };
	int bulletspeed = 5;
	Rectangle BulletRect;
public:
	Bullet(bool isRight, Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) { isRight_ = isRight; };
	void Update();
	void CheckCollision(std::vector<Rectangle> platforms);
	void Destroy();
	~Bullet();

};

