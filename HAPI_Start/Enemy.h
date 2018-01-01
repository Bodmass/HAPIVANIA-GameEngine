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

	bool isHardMode{ false };

	
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
	virtual void checkHit(std::vector<Bullet*> b);
	virtual void isHit(int amount);
	virtual void Kill();
	virtual void Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect);
	virtual float CheckDistance(int x1, int y1, int x2, int y2);
	virtual float AngleToTarget(int x1, int y1, int x2, int y2);
	virtual bool ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect);
	virtual void Setup();
};

