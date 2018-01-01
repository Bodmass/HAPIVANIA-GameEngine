#pragma once 
#include <vector>
#include <unordered_map>
#include <HAPI_lib.h>
#include "Texture.h"
#include "Rectangle.h"

class Visualisation
{
private:

	int v_screenX, v_screenY;

	std::unordered_map<std::string, Texture*> SpriteMap; //creates an unordered map for the textures. [index] [texture]

public:
	Visualisation();
	~Visualisation();
	void Blit(BYTE* screen, Rectangle screenRect, Texture* texture, int posX, int posY, int CamX, int CamY); //Blits the Texture Line by Line (NO ALPHA)
	void BlitAlpha(BYTE* screen, Rectangle screenRect, Texture* texture, int posX, int posY, int CamX, int CamY); //Blits the Texture pixel by pixel (WITH ALPHA)
	void loadTexture(std::string tName, std::string fileName, bool hasAlpha = true); //pushes the texture into the SpriteMap
	
	size_t spriteMapSize() { return SpriteMap.size(); }
	Texture* getSprite(std::string tName); //returns the Texture of the specified index in the SpriteMap
	std::unordered_map<std::string, Texture*>& getSpriteMap(); //Returns the SpriteMap
};

