#pragma once
#include "GameObject.h"
#include "CollisionDetection.h"


class Bullet : public GameObject
{
private:
	bool isActive{ false };
	int dir = 0;
	int bulletspeed = 0;
	int bulletDamage = 20;
	Rectangle BulletRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
public:
	Bullet(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};

	void Update(int pX = 0, int pY = 0);

	void CheckCollision(std::vector<Rectangle> platforms);
	void Destroy(); //Deactivates the Bullet

	Rectangle getRect() override { return BulletRect; }
	bool isUp = false;

	//Set Bullet Direction
	enum Facing {
		Left,
		Right,
		Up,
		Down,
		Homing
	};


	bool checkUp() { return isUp; } //Check if the bullet is going up.
	int getDamage() { return bulletDamage = 20; } //Return the Damage the bullet deals
	void setDamage(int damage) { bulletDamage = damage; } //Set the dmamage the bullet deals
	void fire(std::string face); //Fire the Bullet with its specified direction
	bool checkActive() { return isActive; } //Check if the bullet is active
	~Bullet();

};

