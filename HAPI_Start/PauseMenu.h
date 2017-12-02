#pragma once
#include "Scene.h"

class PauseMenu : public Scene
{
private:
	bool BGMPlaying = false;
	Texture* BG = nullptr;
public:
	PauseMenu(Game* game) : Scene(game) {};

	~PauseMenu();

	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
};

