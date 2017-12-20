#pragma once
#include "GameObject.h"
#include "CollisionDetection.h"


class Bullet : public GameObject
{
private:
	bool isActive{ false };
	bool isRight_{ false };
	int bulletspeed = 0;
	Rectangle BulletRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
public:
	Bullet(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	void Update();
	void CheckCollision(std::vector<Rectangle> platforms);
	void Destroy();
	Rectangle getRect() override { return BulletRect; }
	void fire(bool isRight);
	bool checkActive() { return isActive; }
	~Bullet();

};

