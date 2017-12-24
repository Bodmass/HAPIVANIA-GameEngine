#pragma once
#include "GameObject.h"
#include "SpriteAnimator.h"
#include "Visualisation.h"
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Bullet.h"
#include "Sound.h"
using namespace HAPISPACE;

class Player : public GameObject
{
private:

	//* //* PLAYER \\* \\*
	//STATS
	int p_HP_max = 99;
	int p_HP_cur = p_HP_max;
	int p_speed = 2;
	int p_jumpspeed = 3;
	int p_normaljumpspeed = 3;
	int p_superjumpspeed = 4;

	//BOOLS
	bool p_isShooting{ false };
	bool p_isSprinting{ false };
	bool p_isJumping{ false };
	bool p_isFalling{ false };
	bool p_groundunder{ false };
	bool p_isMoving{ false };
	bool p_isLeft{ false };
	bool p_isRight{ false };
	bool p_isAlive{ true };

	bool p_Immunity{ false };
	int p_Immunity_Delay = 1;

	//PLAYER UPGRADE
	bool upgrade_SPRINT{ false };
	bool upgrade_SUPER_JUMP{ false };
	bool upgrade_XRAY_BEAM{ false };
	bool upgrade_TEMP{ false };

	//MISC
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	int gameClock;
	int p_jumpingtime = 0;
	int p_shootingtime = 0;
	int p_shootingdelay = 300;
	int p_Immunity_Time = 0;

	//FUNCTIONS
	bool p_leftCol{ false };
	bool p_rightCol{ false };
	bool p_Col{ false };


	bool PlayerImmunityCheck();
	void PlayerMovement();
	void PlayerJump();


	//COLLISION
	Rectangle playerfeet;
	Rectangle playerleft;
	Rectangle playerright;
	Rectangle player3;

	//ANIMATION / TEXTURES
	//Animations
	Texture* pSprite = nullptr;
	Texture* pSprite_LeftIdle = nullptr;
	Texture* pSprite_RightIdle = nullptr;
	SpriteAnimator* pAnim_LeftRun = nullptr;
	SpriteAnimator* pAnim_RightRun = nullptr;
	SpriteAnimator* pAnim_LeftSprint = nullptr;
	SpriteAnimator* pAnim_RightSprint = nullptr;
	SpriteAnimator* pAnim_LeftJump = nullptr;
	SpriteAnimator* pAnim_RightJump = nullptr;
	Texture* pSprite_RightFall = nullptr;
	Texture* pSprite_LeftFall = nullptr;

public:
	//void PlayerMove(HAPI_TKeyboardData &keyCode);
	Player(Texture* texture, Rectangle rectangle, int posX, int posY) : GameObject(texture, rectangle, posX, posY) {};
	~Player();
	//Player player;

	void PlayerCollision(std::vector<Rectangle> platforms, Rectangle camRect);
	void PlayerPickup(Rectangle pickup);
	void PlayerUpdate();
	bool PlayerShoot(std::vector<Bullet*> bullets);
	int p_getSpeed() { return p_speed; }
	int p_getcurHP() { return p_HP_cur; }
	bool p_getSprintInfo() { return p_isSprinting; }

	bool p_CheckAlive() { return p_isAlive; }

	//FACING
	bool FacingLeft() { return p_isLeft; }
	bool FacingRight() { return p_isRight; }

	//UPGRADES
	bool checkSprintUpgrade() { return upgrade_SPRINT; }
	void setSprintUpgrade() { upgrade_SPRINT = true; }
	bool checkJumpUpgrade() { return upgrade_SUPER_JUMP; }
	void setJumpUpgrade() { upgrade_SUPER_JUMP = true; }
	bool checkXRAYUpgrade() { return upgrade_XRAY_BEAM; }
	void setXRAYUpgrade() { upgrade_XRAY_BEAM = true; }

	//ANIMATIONS
	void MakeAnims();
	
	void checkHit(std::vector<Bullet*> b, int dmg);
	void Attacked(int damage);
	void AttackedUC(int damage);

	void set_pSprite(Texture* sprite) { pSprite = sprite; }
	void set_pSprite_LeftIdle(Texture* sprite) { pSprite_LeftIdle = sprite; }
	void set_pSprite_RightIdle(Texture* sprite) { pSprite_RightIdle = sprite; }
	void set_pSprite_RightFall(Texture* sprite) { pSprite_RightFall = sprite; }
	void set_pSprite_LeftFall(Texture* sprite) { pSprite_LeftFall = sprite; }
	//
	void set_pAnim_LeftRun(SpriteAnimator* anim) { pAnim_LeftRun = anim; }
	void set_pAnim_RightRun(SpriteAnimator* anim) { pAnim_RightRun = anim; }
	void set_pAnim_LeftSprint(SpriteAnimator* anim) { pAnim_LeftSprint = anim; }
	void set_pAnim_RightSprint(SpriteAnimator* anim) { pAnim_RightSprint = anim; }
	void set_pAnim_LeftJump(SpriteAnimator* anim) { pAnim_LeftJump = anim; }
	void set_pAnim_RightJump(SpriteAnimator* anim) { pAnim_RightJump = anim; }

	Texture* get_pSprite() { return pSprite; }
	Texture* get_pSprite_LeftIdle() { return pSprite_LeftIdle; }
	Texture* get_pSprite_RightIdle() { return pSprite_RightIdle; }
	Texture* get_pSprite_RightFall() { return pSprite_RightFall; }
	Texture* get_pSprite_LeftFall() { return pSprite_LeftFall; }
	SpriteAnimator* get_pAnim_LeftRun() { return pAnim_LeftRun; }
	SpriteAnimator* get_pAnim_RightRun() { return pAnim_RightRun; }
	SpriteAnimator* get_pAnim_LeftSprint() { return pAnim_LeftSprint; }
	SpriteAnimator* get_pAnim_RightSprint() { return pAnim_RightSprint; }
	SpriteAnimator* get_pAnim_LeftJump() { return pAnim_LeftJump; }
	SpriteAnimator* get_pAnim_RightJump() { return pAnim_RightJump; }

	Rectangle getPlayerRect() { return player3; }
	
};

