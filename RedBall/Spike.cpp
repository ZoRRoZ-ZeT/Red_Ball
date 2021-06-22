#include "Spike.h"

Spike::Spike(sf::Vector2f _position, sf::Vector2f _size, std::string path)
	:Obstacle(_position, _size, path)
{
}

void Spike::Render(sf::RenderWindow * target)
{
	target->draw(this->GetSprite());
}
