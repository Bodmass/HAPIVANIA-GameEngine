#pragma once
#include "Scene.h"

class EndScene : public Scene
{
private:
	bool BGMPlaying = false;
	Texture* BG = nullptr;
	Texture* Credits = nullptr;
	Texture* Credits2 = nullptr;
	GameObject* creditstext1;
	GameObject* creditstext2;
	std::vector<GameObject*> gameObjects;
public:
	EndScene(Game* game) : Scene(game) {};

	int fadecount = 0;

	~EndScene();

	virtual void update() override;
	virtual void render() override;
	virtual void loadTextures() override;
	virtual void loadGameObject() override;
	virtual void loadSounds() override;
};

