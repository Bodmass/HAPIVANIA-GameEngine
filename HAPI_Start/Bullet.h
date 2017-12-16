#pragma once
#include "GameObject.h"
#include "CollisionDetection.h"

class Bullet : public GameObject
{
private:
	bool isRight_{ false };
	int bulletspeed = 0;
	Rectangle BulletRect;
public:
	Bullet(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	void Update();
	void CheckCollision(std::vector<Rectangle> platforms);
	void Destroy();
	void fire(bool isRight);
	~Bullet();

};

