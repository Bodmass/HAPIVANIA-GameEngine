#pragma once
#include "GameObject.h"
#include "CollisionDetection.h"


class Bullet : public GameObject
{
private:
	bool isActive{ false };
	int dir = 0;
	int bulletspeed = 0;
	Rectangle BulletRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
public:
	Bullet(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	void Update(int pX = 0, int pY = 0);
	void CheckCollision(std::vector<Rectangle> platforms);
	void Destroy();
	Rectangle getRect() override { return BulletRect; }
	bool isUp = false;
	enum Facing {
		Left,
		Right,
		Up,
		Down,
		Homing
	};
	bool checkUp() { return isUp; }
	void fire(std::string face);
	bool checkActive() { return isActive; }
	~Bullet();

};

