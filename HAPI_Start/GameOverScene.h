#pragma once
#include "Scene.h"
class GameOverScene :
	public Scene
{
	
private:
	bool BGMPlaying = false;
	Texture* BG = nullptr;
	int gameClock = 0;
	int delayClock = 0;
	bool setup = false;

public:
	GameOverScene(Game* game) : Scene(game) {};
	~GameOverScene();

	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
	virtual void loadSounds() override;
};

