#pragma once

#include <HAPI_lib.h>
#include <string>

using namespace HAPISPACE;

class Texture
{
private:
	int t_Width, t_Height;
	std::string fileName;
	BYTE* t_sprite{nullptr};
	bool hasAlpha_{ true };
	bool isEntity_{ false };
public:
	Texture() {};
	Texture(std::string filename, bool hasAlpha = true);
	virtual ~Texture();
	//Returns the BYTE* of the Sprite
	virtual BYTE* getSprite();
	virtual bool getAlpha() { return hasAlpha_; };
	virtual int getWidth() { return t_Width; };
	virtual int getHeight() { return t_Height; };
	bool checkEntity() { return isEntity_; };
	bool setEntity() { return isEntity_ = true; };

};

