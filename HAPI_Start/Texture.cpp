#include "Texture.h"

//textures::textures(const textures & other) //TEST
//{
//	t_sprite = new BYTE[other.t_Width * other.t_Height * 4]();
//	memcpy(t_sprite, other.t_sprite, other.t_Width * other.t_Height * 4);
//}

Texture::Texture(std::string filename, bool hasAlpha) : fileName(filename), hasAlpha_(hasAlpha)
{

	if (!HAPI.LoadTexture(filename, &t_sprite, t_Width, t_Height))
		HAPI.UserMessage("The Texture was unable to be loaded", "Ohh noooo");
	
}


Texture::~Texture()
{
	if (t_sprite != nullptr)
	{
		delete[] t_sprite; //TO BE FIXED
	}
		
}

BYTE* Texture::getSprite()
{
	return t_sprite;
}
