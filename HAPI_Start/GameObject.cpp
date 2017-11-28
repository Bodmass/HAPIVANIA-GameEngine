#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(Texture* texture, Rectangle rectangle, int posX, int posY, bool isBG)
{
	texture_ = texture;
	rectangle_ = rectangle;
	positionX = posX;
	positionY = posY;

	if(!isBG)
		texture_->setEntity();
}

GameObject::~GameObject()
{
}
