#pragma once

#include <HAPI_lib.h>
#include <string>

using namespace HAPISPACE;

class Texture
{
private:
	int t_Width, t_Height;
	std::string tName;
	BYTE* t_sprite{nullptr};
	bool hasAlpha_{ true };
	bool isEntity_{ false };
	int t_X = 1;
	int t_Y = 1;
public:
	Texture() {};
	/*textures(const textures& other);*/
	Texture(std::string filename, bool hasAlpha = true);
	~Texture();
	BYTE* getSprite();
	bool getAlpha() { return hasAlpha_; };
	int getWidth() { return t_Width; };
	int getHeight() { return t_Height; };
	bool checkEntity() { return isEntity_; };
	bool setEntity() { return isEntity_ = true; };
	int &getPosX() { return t_X; };
	int &getPosY() { return t_Y; };
};

