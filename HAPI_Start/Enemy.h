#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy : 
	public GameObject
{
protected:

	//Enemy Stats
	int e_HP{ 20 };
	int e_Damage_Min{ 3 };
	int e_Damage_Max{ 10 };
	bool e_isAlive{ true };
	int threshold = 300;
	int attack_range = 30;

	int origin_x = getX();
	int origin_y = getY();

	bool isHardMode{ false }; //Sets the Enemy to Hard Mode

	
	//Enemy Settings
	int state = 0;
	enum State {
		Idle,
		Follow,
		Return
	};
public:
	Enemy(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	~Enemy();
	virtual void setHardMode() { isHardMode = true; }
	virtual void checkHit(std::vector<Bullet*> b); //Check if the Enemy is hit by a bullet
	virtual void isHit(int amount); //Hit the Enemy with the Specified Amount
	virtual void Kill(); //Kill the Enemy
	virtual void Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect); 
	virtual float CheckDistance(int x1, int y1, int x2, int y2); //Gets the Distance between the Player and the Enemy
	virtual float AngleToTarget(int x1, int y1, int x2, int y2); //Gets the Angle between the Player and the Enemy
	virtual bool ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect); //Check if the Enemy has reacted the end of a platform
	virtual void Setup(); //Setup the Enemy (affected in the overrides)
};

