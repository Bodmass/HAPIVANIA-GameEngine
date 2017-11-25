/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there are two batch files for creating a redistributable Demo folder
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include "visualisation.h"
#include <algorithm>
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

HAPI_TColour setColour(BYTE* screen, int width, int height, int r, int g, int b, int a);
// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	int screenWidth = 900;
	int screenHeight = 600;

	visualisation graphics;



	if (!HAPI.Initialise(screenWidth, screenHeight, "Textures & Blitting"))
		return;

	BYTE* screen = HAPI.GetScreenPointer();

	graphics.loadTexture("Data/background.tga");
	graphics.loadTexture("Data/alphaThing.tga");
	
	int posX{ 1 }, posY{ 1 };

	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();



	while (HAPI.Update())
	{
		//std::cerr<< screenWidth << screenHeight <<std::endl;
		setColour(screen, screenWidth, screenHeight, 0, 0, 0, 255); //Clear screen to colour
		for (size_t i = 0; i < graphics.getSpriteMap().size(); i++)
		{
			if(graphics.getSprite(i)->getAlpha())
				graphics.BlitAlpha(screen, screenWidth, graphics.getSprite(i));
			else
				graphics.Blit(screen, screenWidth, graphics.getSprite(i));
			//std::cerr << "Ran this " << i + 1 << " time(s)" << std::endl;
		}

		if (keyData.scanCode[HK_DOWN])
			graphics.getSprite(1)->getPosY() += 1;
		if (keyData.scanCode[HK_UP])
			graphics.getSprite(1)->getPosY() -= 1;
		if (keyData.scanCode[HK_LEFT])
			graphics.getSprite(1)->getPosX() -= 1;
		if (keyData.scanCode[HK_RIGHT])
			graphics.getSprite(1)->getPosX() += 1;

		//Limit the min and max of the Positions
		graphics.getSprite(1)->getPosX() = std::max(0, std::min(screenWidth - graphics.getSprite(1)->getWidth(), graphics.getSprite(1)->getPosX()));
		graphics.getSprite(1)->getPosY() = std::max(0, std::min(screenHeight - graphics.getSprite(1)->getHeight(), graphics.getSprite(1)->getPosY()));

		HAPI.RenderText(0, 0, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2, "Texture Blitting", 22);

	}

}

HAPI_TColour setColour(BYTE* screen, int width, int height, int r, int g, int b, int a)
{
	HAPI_TColour col{ HAPI_TColour(r,g,b) };

	for (int i = 0; i < width*height; i++)
	{
		screen[i*4] = col.red;
		screen[i*4+1] = col.green;
		screen[i*4+2] = col.blue;
		screen[i*4+3] = col.alpha;
	}

	return col;
}
