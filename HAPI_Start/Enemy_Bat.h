#pragma once
#include "Enemy.h"

class Enemy_Bat: public Enemy
{
private:
	Texture* pSprite_Idle = nullptr;
	SpriteAnimator* pAnim_LeftRun = nullptr;
	SpriteAnimator* pAnim_RightRun = nullptr;


	int e_HP{ 40 };
	int e_Damage_Min{ 1 };
	int e_Damage_Max{ 4 };
	int threshold = 100;

	double e_Speed{ 3 };

	int gameClock = 0;
	int attackClock = 0;


public:
	Enemy_Bat(Texture* texture, Rectangle rectangle, int posX, int posY) : Enemy(texture, rectangle, posX, posY) {};
	~Enemy_Bat();

	void Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect) override;

	Texture* get_pSprite_Idle() { return pSprite_Idle; }
	SpriteAnimator* get_pAnim_LeftRun() { return pAnim_LeftRun; }
	SpriteAnimator* get_pAnim_RightRun() { return pAnim_RightRun; }

	void set_pSprite_Idle(Texture* sprite) { pSprite_Idle = sprite; }
	void set_pAnim_LeftRun(SpriteAnimator* anim) { pAnim_LeftRun = anim; }
	void set_pAnim_RightRun(SpriteAnimator* anim) { pAnim_RightRun = anim; }
	bool ReachedEnd(std::vector<Rectangle> platforms, Rectangle camRect) override;
	void BatConflict(Enemy* enemies);
};