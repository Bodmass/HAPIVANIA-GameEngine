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

	std::unordered_map<int, Texture*> SpriteMap; //creates an unordered map for the textures. [index] [texture]
	int index{ 0 }; //the first index of the SpriteMap

	

	//Texture* getSprite(int i); //returns the Texture of the specified index in the SpriteMap
	//std::unordered_map<int, Texture*>& getSpriteMap(); //Returns the SpriteMap
public:
	Visualisation();
	~Visualisation();
	void Blit(BYTE* screen, Rectangle screenRect, Texture* texture, int posX, int posY, int CamX, int CamY); //Blits the Texture Line by Line (NO ALPHA)
	void BlitAlpha(BYTE* screen, Rectangle screenRect, Texture* texture, int posX, int posY, int CamX, int CamY); //Blits the Texture pixel by pixel (WITH ALPHA)
	void loadTexture(std::string tName, bool hasAlpha = true); //pushes the texture into the SpriteMap
	
	int spriteMapSize() { return SpriteMap.size(); }
	//MOVE THIS TO PRIVATE
	Texture* getSprite(int i); //returns the Texture of the specified index in the SpriteMap
	std::unordered_map<int, Texture*>& getSpriteMap(); //Returns the SpriteMap
};

