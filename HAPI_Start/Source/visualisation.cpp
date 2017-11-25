#include "visualisation.h"
#include <vector>


visualisation::visualisation()
{
}


visualisation::~visualisation()
{
	
}

void visualisation::Blit(BYTE *screen, int screenWidth, textures* texture)
{
	int textureWidth = texture->getWidth();
	int textureHeight = texture->getHeight();

	int texturePosX{ texture->getPosX() }, texturePosY{ texture->getPosY() };

	


	BYTE* screenPtr = screen + (texturePosX + texturePosY*screenWidth) * 4;

	BYTE* texturePtr = texture->getSprite();

	for (int y = 0; y < textureHeight; y++)
	{
		memcpy(screenPtr, texturePtr, textureWidth * 4);

		texturePtr += textureWidth * 4;
		screenPtr += screenWidth * 4;
	}
}

void visualisation::BlitAlpha(BYTE * screen, int screenWidth, textures* texture)
{
	int textureWidth = texture->getWidth();
	int textureHeight = texture->getHeight();

	int texturePosX{ texture->getPosX() }, texturePosY{ texture->getPosY() };

	//std::cerr << texture->getPosX();

	BYTE* screenPtr = screen + (texturePosX + texturePosY*screenWidth) * 4;

	BYTE* texturePtr = texture->getSprite();

	

	for (int y = 0; y < textureHeight-1; y++)
	{
		for (int x = 0; x < textureWidth-1; x++)
		{
			BYTE blue = texturePtr[0+x*4];
			BYTE green = texturePtr[1 + x * 4];
			BYTE red = texturePtr[2 + x * 4];
			BYTE alpha = texturePtr[3 + x * 4];
			BYTE* currentPixel = screenPtr + x * 4;
			
			
			currentPixel[0] = currentPixel[0] + ((alpha*(blue - currentPixel[0])) >> 8);
			currentPixel[1] = currentPixel[1] + ((alpha*(green - currentPixel[1])) >> 8);
			currentPixel[2] = currentPixel[2] + ((alpha*(red - currentPixel[2])) >> 8);
		

		}
		texturePtr += textureWidth * 4;
		screenPtr += screenWidth * 4;
	}
}

void visualisation::loadTexture(std::string tName) //Pushes new texture into the vector
{
	SpriteMap[index] = tName;
	index += 1;
}

textures* visualisation::getSprite(int index) //Returns the Vectors sprite
{
	return &SpriteMap[index];
}


std::unordered_map<int, textures>& visualisation::getSpriteMap()
{
	return SpriteMap;
}

