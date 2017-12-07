#pragma once
#include "GameObject.h"
#include "Player.h"
class Pickup :
	public GameObject
{
private:
	int p_ID;
	bool Collected = false;
public:
	Pickup(int p_ID_, Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) { p_ID = p_ID_; };
	~Pickup();
	void Update(Player* plyr);
	bool CheckCollected() { return Collected; }
};

