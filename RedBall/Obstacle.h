#pragma once
#include "stdafx.h"
class Obstacle
{
private:
	sf::Vector2f position;
	sf::Vector2f size;

	sf::Texture texture;
	sf::Sprite sprite;
public:
	Obstacle(sf::Vector2f _position, sf::Vector2f _size, std::string path);

	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow * target) = 0;

	sf::Sprite GetSprite();
};

