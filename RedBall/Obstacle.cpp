#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f _position, sf::Vector2f _size, std::string path)
{
	this->position = _position;
	this->size = _size;

	this->texture.loadFromFile(path);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(this->position);
	this->sprite.setTextureRect(sf::IntRect(0, 0, this->size.x, this->size.y));
}

sf::Sprite Obstacle::GetSprite()
{
	return this->sprite;
}
