#pragma once
#include "GameObject.h"
#include "Visualisation.h"
#include "Player.h"
#include "CollisionDetection.h"


class Pickup : public GameObject
{
private:
	int p_ID;
	Rectangle PickupRect;
	bool Collected = false;
public:
	Pickup(int id, Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) { p_ID = id; };
	~Pickup();
	void Update(Player* plyr);
	void PickedUp(Player* plyr);
	bool CheckCollected() { return Collected; }
	void Destroy();
};

//p_ID
//0 - Health
//1 - Sprint Upgrade
//2 - Jump Upgrade
//3 - Xray Beam
//4 - ???

