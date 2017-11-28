#pragma once
#include "Texture.h"
#include <vector>
#include "HAPI_lib.h"


class SpriteAnimator: public Texture
{
private:
	float startTime = 0;
	int framerate = 10;
	std::vector<Texture*> frames;
public:
	SpriteAnimator();
	~SpriteAnimator();
	void addFrame(Texture* texture) { frames.push_back(texture); }
	void play() { startTime = HAPI.GetTime(); }
	//Texture* getSprite() override;
};

