#include "SpriteAnimator.h"



Texture * SpriteAnimator::getTexture()
{
	HAPISPACE::DWORD curTime = HAPI.GetTime();

	int framesSinceStart = (int)((curTime - startTime) / framerate);
	int currentFrameIndex = framesSinceStart % frames.size();

	return frames[currentFrameIndex];
}

SpriteAnimator::SpriteAnimator()
{
	setEntity();
}


SpriteAnimator::~SpriteAnimator()
{
}

HAPISPACE::BYTE * SpriteAnimator::getSprite()
{
	HAPISPACE::DWORD curTime = HAPI.GetTime();

	int framesSinceStart = (int)((curTime - startTime) / (float)framerate);
	int currentFrameIndex = framesSinceStart % frames.size();
	
	return frames[currentFrameIndex]->getSprite();
}
