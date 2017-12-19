#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy : 
	public GameObject
{
private:

	//Enemy Stats
	int e_HP{ 100 };
	int e_Damage{ 10 };
	bool e_isAlive{ true };
	int threshold = 300;
	int attack_range = 30;

	
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
	void Kill() { e_isAlive = false; }
	void Update(Player* plyr);
	float CheckDistance(int x1, int y1, int x2, int y2);
	float AngleToTarget(int x1, int y1, int x2, int y2);
};

