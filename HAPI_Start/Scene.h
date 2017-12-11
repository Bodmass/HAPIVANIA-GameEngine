#pragma once

#include <HAPI_lib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "Visualisation.h"
#include "Rectangle.h"
#include "GameObject.h"
#include "SpriteAnimator.h"
#include "Sound.h"

using namespace HAPISPACE;

class Game;
class Scene
{

private:

	bool BGMPlaying = false;
protected:
	Game* game_ = nullptr;
public:
	virtual void update() {};
	virtual void render() {};
	virtual void loadTextures() {};
	virtual void loadGameObject() {};
	virtual void loadSounds() {};
	Scene(Game* game) { game_ = game; };
	virtual~Scene() {};
	virtual Game* getGame() { return game_; }
};


