#include "Warp.h"
#include "CollisionDetection.h"


Warp::~Warp()
{
}

void Warp::Update(Rectangle* plyrRect)
{
	Rectangle WarpRect = Rectangle(this->getTexture()->getWidth(), this->getTexture()->getHeight());
	WarpRect.Translate(getX(), getY());

	if (CollisionDetection::CheckCollision(*plyrRect, WarpRect))
	{
		hasEntered = true;
	}
}
