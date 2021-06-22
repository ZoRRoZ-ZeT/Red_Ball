#pragma once
#include "Obstacle.h"
class Spike :
	public Obstacle
{
private:

public:
	Spike(sf::Vector2f _position, sf::Vector2f _size, std::string path);

	void Update() { };
	void Render(sf::RenderWindow * target);
};
