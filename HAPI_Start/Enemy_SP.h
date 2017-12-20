#pragma once
#include "Enemy.h"
class Enemy_SP :
	public Enemy
{
private:
	Texture* pSprite_LeftIdle = nullptr;
	Texture* pSprite_RightIdle = nullptr;
	SpriteAnimator* pAnim_LeftRun = nullptr;
	SpriteAnimator* pAnim_RightRun = nullptr;



public:
	Enemy_SP(Texture* texture, Rectangle rectangle, int posX, int posY) : Enemy(texture, rectangle, posX, posY) {};
	~Enemy_SP();

	void Update(Player* plyr, std::vector<Rectangle> platforms, Rectangle camRect) override;

	Texture* get_pSprite_LeftIdle() { return pSprite_LeftIdle; }
	Texture* get_pSprite_RightIdle() { return pSprite_RightIdle; }
	SpriteAnimator* get_pAnim_LeftRun() { return pAnim_LeftRun; }
	SpriteAnimator* get_pAnim_RightRun() { return pAnim_RightRun; }

	//void set_pSprite(Texture* sprite) { pSprite = sprite; }
	void set_pSprite_LeftIdle(Texture* sprite) { pSprite_LeftIdle = sprite; }
	void set_pSprite_RightIdle(Texture* sprite) { pSprite_RightIdle = sprite; }
	void set_pAnim_LeftRun(SpriteAnimator* anim) { pAnim_LeftRun = anim; }
	void set_pAnim_RightRun(SpriteAnimator* anim) { pAnim_RightRun = anim; }
};

