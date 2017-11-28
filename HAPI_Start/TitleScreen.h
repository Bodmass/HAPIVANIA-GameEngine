#pragma once
#include "GameScene.h"

class TitleScreen : public GameScene
{
private:
	bool BGMPlaying = false;
	Texture* BG = nullptr;
public:
	TitleScreen(Game* game) : GameScene(game) {};

	~TitleScreen();

	virtual void update() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
};

