#pragma once
#include "GameObject.h"
#include "Visualisation.h"
#include "Player.h"
#include "CollisionDetection.h"


class Pickup : public GameObject
{
private:
	//int p_ID;
	Rectangle PickupRect;
	bool Collected = false;
public:
	Pickup(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	~Pickup();
	void Update(Player* plyr);
	bool CheckCollected() { return Collected; }
	void Destroy();
};

