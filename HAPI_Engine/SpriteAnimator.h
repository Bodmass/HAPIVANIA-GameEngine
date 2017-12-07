#pragma once
#include "Texture.h"
#include <vector>
#include "HAPI_lib.h"


class SpriteAnimator: public Texture
{
private:
	float startTime = 0;
	int framerate = 100;
	std::vector<Texture*> frames;
	Texture* getTexture();
public:
	SpriteAnimator();
	~SpriteAnimator();
	void addFrame(Texture* texture) { frames.push_back(texture); }
	void play() { startTime = HAPI.GetTime(); }
	HAPISPACE::BYTE* getSprite() override;
	bool getAlpha() { return getTexture()->getAlpha(); };
	int getWidth() { return getTexture()->getWidth(); };
	int getHeight() { return getTexture()->getHeight(); };
};

