#pragma once
#include "Enemy.h"
class Boss : public Enemy
{
private:
	SpriteAnimator * pSprite_Idle = nullptr;
	
	int e_Damage_Min{ 10 };
	int e_Damage_Max{ 20 };
	int threshold = 100;

	enum Direction {
		Left,
		Right
	};
	enum Phase {
		Phase1,
		Phase2,
		Phase3
	};
	enum Moves {
		DoubleBeam,
		HomingMissile,
		Other
	};

	double e_Speed{ 2 };

	int gameClock = 0;
	int attackClock = 0;
	int swapClock = 0; //Swaps Attacking Method
	bool isSetup{ false };
	bool isActive{ false };
	int phase = 0;

	int dir = 0;
	Moves atk = DoubleBeam;


public:
	Boss(Texture* texture, Rectangle rectangle, int posX, int posY) : Enemy(texture, rectangle, posX, posY) {};
	~Boss();

	void Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect) override;

	SpriteAnimator* get_pSprite_Idle() { return pSprite_Idle; }

	void Activate();
	void set_pSprite_Idle(SpriteAnimator* sprite) { pSprite_Idle = sprite; }
	bool ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect) override;
	void checkHit(std::vector<Bullet*> b) override;
	bool Shoot(std::vector<Bullet*> b);
};

