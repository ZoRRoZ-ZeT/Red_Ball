#pragma once
#include "Obstacle.h"

class Flag :
	public Obstacle
{
private:

public:
	Flag(sf::Vector2f _position, sf::Vector2f _size, std::string path);

	void Update() { };
	void Render(sf::RenderWindow * target);

};

