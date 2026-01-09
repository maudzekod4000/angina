#include "GameObject.h"

GameObject::GameObject(ID id, Sprite& sprite, float speedFactor, Point pos, Dimensions dim):
	id(id),
	sprite(sprite),
	speedFactor(speedFactor),
	renderingPos(pos),
	placementPos(pos),
	dim(dim),
	dir(Point()),
	box(BoundingBox())
{
	calculateBB();
}

GameObject::GameObject(ID id, Point pos, Dimensions dim):
	id(id),
	renderingPos(pos),
	placementPos(pos),
	dim(dim),
	dir(Point()),
	box(BoundingBox())
{
	calculateBB();
}

void GameObject::updatePosition(const Point &placementPos, Direction dir)
{
	this->renderingPos = placementPos;
	this->placementPos = placementPos;
	calculateBB();
}

void GameObject::updateDirection(const Point& newDir)
{
	this->dir = newDir;
}

void GameObject::rememberCollision()
{
}

void GameObject::setSprite(Sprite s)
{
	this->sprite = s;
}

void GameObject::setDirection(const Point& dir)
{
	this->dir = dir;
}

void GameObject::calculateBB()
{
	Point min{ this->renderingPos.x, this->renderingPos.y + this->dim.h };
	Point max{ this->renderingPos.x + this->dim.w, this->renderingPos.y };
	this->box = BoundingBox(min, max);
}

ForwardIdGenerator GameObjectFactory::idgen;
