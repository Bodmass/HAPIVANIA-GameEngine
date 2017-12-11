#pragma once
#include "Scene.h"

class TitleScreen : public Scene
{
private:
	bool BGMPlaying = false;
	Texture* BG = nullptr;
public:
	TitleScreen(Game* game) : Scene(game) {};

	~TitleScreen();

	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
	virtual void loadSounds() override;
};

