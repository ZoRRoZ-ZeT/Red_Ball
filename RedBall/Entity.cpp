#include "Entity.h"

Entity::Entity(sf::Vector2f _position, int _maxSpeed, int _w, int _h)
{
	this->position = _position;
	this->maxSpeed = _maxSpeed;

	this->size = sf::Vector2f(_w, _h);
}

Entity::~Entity()
{

}

void Entity::SetTexture(sf::Texture texture)
{
	this->entityTexture = texture;
	this->entitySprite.setTexture(this->entityTexture);
}

sf::Vector2f Entity::GetPosition() const
{
	return this->position;
}

sf::Sprite Entity::GetSprite() const
{
	return this->entitySprite;
}

float Entity::GetSpeed() const
{
	return this->speed;
}

float Entity::GetMaxSpeed() const
{
	return this->maxSpeed;
}

sf::Vector2f Entity::GetSize() const
{
	return this->size;
}

void Entity::SetSpeed(float val)
{
	if (abs(val) >= this->maxSpeed)
		this->speed = this->maxSpeed * val / abs(val);
	else
		this->speed = val;
}

void Entity::SetPostion(sf::Vector2f _newPosition)
{
	this->position = _newPosition;
}
