#include "textures.h"

//textures::textures(const textures & other) //TEST
//{
//	t_sprite = new BYTE[other.t_Width * other.t_Height * 4]();
//	memcpy(t_sprite, other.t_sprite, other.t_Width * other.t_Height * 4);
//}

textures::textures(std::string filename) : tName(filename)
{

	if (!HAPI.LoadTexture(filename, &t_sprite, t_Width, t_Height))
		HAPI.UserMessage("The Texture was unable to be loaded", "Ohh noooo");
	

	t_X = 1;
	t_Y = 1;
}


textures::~textures()
{
//	if (t_sprite != nullptr)
	{
		//delete[] t_sprite; //TO BE FIXED
	}
		
}

BYTE* textures::getSprite()
{
	return t_sprite;
}
