#pragma once
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
using namespace HAPISPACE;

class Player
{
private:
	int p_HP = 100;
public:
	void PlayerMove(HAPI_TKeyboardData &keyCode);
	Player();
	~Player();
};

