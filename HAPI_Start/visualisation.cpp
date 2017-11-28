#include "Visualisation.h"
#include <vector>
#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */


Visualisation::Visualisation()
{
}


Visualisation::~Visualisation()
{
	for (int i = 0; i<index; i++)
	{
		//delete SpriteMap[i]->getSprite();
		delete SpriteMap[i];
		//SpriteMap.erase(i);
	}
	SpriteMap.clear();
}

void Visualisation::Blit(BYTE *screen, Rectangle screenRect, Texture* texture, int posX, int posY, int CamX, int CamY)
{
	int screenWidth = screenRect.getWidth();
	int screenHeight = screenRect.getHeight();

	int textureWidth = texture->getWidth();
	int textureHeight = texture->getHeight();

	int texturePosX{ posX }, texturePosY{ posX };

	if (texture->checkEntity())
	{
		texturePosX = posX + CamX;
		texturePosY = posY + CamY;
	}
	
	Rectangle spriteRect = Rectangle(texture->getWidth(), texture->getHeight());
	spriteRect.Translate(texturePosX, texturePosY);
	spriteRect = screenRect.rContains(spriteRect);
	if (spriteRect.getWidth() <= 0 && spriteRect.getHeight() <= 0)
		return; //Returns if Sprite is off screen

	Rectangle clippedRect = spriteRect;
	clippedRect.Translate(-texturePosX, -texturePosY);

	BYTE* screenPtr = screen;
	BYTE* texturePtr = texture->getSprite();

	if (!screenPtr || !texturePtr)
	{
		return;
	}

	screenPtr = screen + ((texturePosX + clippedRect.getLeft()) + (texturePosY + clippedRect.getTop())*screenWidth) * 4;

	texturePtr = texture->getSprite() + (clippedRect.getTop() * textureWidth * 4) + (clippedRect.getLeft() * 4);

	for (int y = 0; y < clippedRect.getHeight(); y++)
	{
		memcpy(screenPtr, texturePtr, clippedRect.getWidth() * 4);

		texturePtr += textureWidth * 4;
		screenPtr += screenWidth * 4;
	}
}

void Visualisation::BlitAlpha(BYTE* screen, Rectangle screenRect, Texture* texture, int posX, int posY, int CamX, int CamY)
{

	int screenWidth = screenRect.getWidth();
	int screenHeight = screenRect.getHeight();

	//Rectangle cameraRect = Rectangle(screenWidth, screenHeight);
	
	//cameraRect.Translate(CamX, CamY);


	int textureWidth = texture->getWidth();
	int textureHeight = texture->getHeight();

	int texturePosX{ posX}, texturePosY{ posX };

	if (texture->checkEntity())
	{
		texturePosX = posX + CamX;
		texturePosY = posY + CamY;
	}


	Rectangle spriteRect = Rectangle(texture->getWidth(), texture->getHeight());
	spriteRect.Translate(texturePosX, texturePosY);
	spriteRect = screenRect.rContains(spriteRect);
	if (spriteRect.getWidth() <= 0 && spriteRect.getHeight() <= 0)
		return; //Returns if Sprite is off screen

	Rectangle clippedRect = spriteRect;
	clippedRect.Translate(-texturePosX , -texturePosY);

	BYTE* screenPtr = screen + ((texturePosX) + (texturePosY)*screenWidth) * 4;

	BYTE* texturePtr = texture->getSprite();

	if (texture->checkEntity())
	{

		for (int y = 0; y < clippedRect.getHeight() - 1; y++)
		{


			for (int x = 0; x < clippedRect.getWidth() - 1; x++)
			{

				screenPtr = screen + (((texturePosX + clippedRect.getLeft()) + (texturePosY + clippedRect.getTop())*screenWidth) * 4) + (y*screenWidth * 4) + (x * 4);
				texturePtr = texture->getSprite() + ((y + clippedRect.getTop()) * textureWidth * 4) + ((x + clippedRect.getLeft()) * 4);

				BYTE blue = texturePtr[0];
				BYTE green = texturePtr[1];
				BYTE red = texturePtr[2];
				BYTE alpha = texturePtr[3];
				BYTE* currentPixel = screenPtr;


				currentPixel[0] = currentPixel[0] + ((alpha*(blue - currentPixel[0])) >> 8);
				currentPixel[1] = currentPixel[1] + ((alpha*(green - currentPixel[1])) >> 8);
				currentPixel[2] = currentPixel[2] + ((alpha*(red - currentPixel[2])) >> 8);


			}

		}
	}
	else {
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
}

void Visualisation::loadTexture(std::string tName, bool hasAlpha) //Pushes new texture into the vector
{
	SpriteMap[index] = new Texture(tName, hasAlpha);
	index += 1;
}

Texture* Visualisation::getSprite(int index) //Returns the Vectors sprite
{
	return SpriteMap[index];
}


std::unordered_map<int, Texture*>& Visualisation::getSpriteMap()
{
	return SpriteMap;
}

