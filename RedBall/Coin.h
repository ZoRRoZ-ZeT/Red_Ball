#pragma once
#include "Obstacle.h"
class Coin :
	public Obstacle
{
private:

public:
	Coin(sf::Vector2f _position, sf::Vector2f _size, std::string path);

	void Update() { };
	void Render(sf::RenderWindow * target);
};
