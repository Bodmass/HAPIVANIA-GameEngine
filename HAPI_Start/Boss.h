#pragma once
#include "Enemy.h"
class Boss : public Enemy
{
private:
	SpriteAnimator * pSprite_Idle = nullptr;
	
	int e_Damage_Min{ 10 };
	int e_Damage_Max{ 20 };
	int threshold = 100;

	double e_Speed{ 2 };

	int gameClock = 0;
	int attackClock = 0;
	bool isSetup{ false };
	bool isActive{ false };
	int phase = 0;
	int dir = 0;
	enum Direction {
		Left,
		Right
	};
	enum Phase {
		Phase1,
		Phase2,
		Phase3
	};


public:
	Boss(Texture* texture, Rectangle rectangle, int posX, int posY) : Enemy(texture, rectangle, posX, posY) {};
	~Boss();

	void Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect) override;

	SpriteAnimator* get_pSprite_Idle() { return pSprite_Idle; }

	void Activate();
	void set_pSprite_Idle(SpriteAnimator* sprite) { pSprite_Idle = sprite; }
	bool ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect) override;
};

