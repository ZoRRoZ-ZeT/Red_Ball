#pragma once
#include "Obstacle.h"
class Block :
	public Obstacle
{
private:

public:
	Block(sf::Vector2f _position, sf::Vector2f _size, std::string path);

	void Update() { };
	void Render(sf::RenderWindow * target);
};

