#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,FILE, LINE)
#endif


#include <HAPI_lib.h>
#include "Game.h"

using namespace HAPISPACE;

void HAPI_Main()
{
	//Creates an instance of the game
	Game game;
	game.Run();
}
