#include <vector>
#include <unordered_map>
#include <HAPI_lib.h>
#include "textures.h"

class visualisation
{
private:

	int v_screenX, v_screenY;

	std::unordered_map<int, textures> SpriteMap; //creates an unordered map for the textures. [index] [texture]
	int index{ 0 }; //the first index of the SpriteMap

public:
	visualisation();
	~visualisation();
	void Blit(BYTE *screen, int screenWidth, textures* texture); //Blits the Texture Line by Line (NO ALPHA)
	void BlitAlpha(BYTE *screen, int screenWidth, textures* texture); //Blits the Texture pixel by pixel (WITH ALPHA)
	void loadTexture(std::string tName); //pushes the texture into the SpriteMap
	
	textures* getSprite(int i); //returns the Texture of the specified index in the SpriteMap
	std::unordered_map<int, textures>& getSpriteMap(); //Returns the SpriteMap
};

