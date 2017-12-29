#pragma once
#include "GameObject.h"
class Warp :
	public GameObject
{
private:
	int WarpID;
	bool hasEntered = false;
public:
	Warp(int WarpID_, Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) { WarpID = WarpID_; };
	~Warp();

	void Update(Rectangle* plyrRect);
	bool Entered() { return hasEntered; }
	bool getID() { return WarpID; }
};

