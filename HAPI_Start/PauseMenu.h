#pragma once
#include "Scene.h"

class PauseMenu : public Scene
{
private:
	bool justopened = true;
	bool BGMPlaying = false;
	Texture* BG = nullptr;
	Texture* Upgrade1 = nullptr;
	Texture* Upgrade2 = nullptr;
	Texture* Upgrade3 = nullptr;

public:
	PauseMenu(Game* game) : Scene(game) {};

	~PauseMenu();

	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
};

