#include "Block.h"

Block::Block(sf::Vector2f _position, sf::Vector2f _size, std::string path)
	:Obstacle(_position, _size, path)
{
}

void Block::Render(sf::RenderWindow * target)
{
	target->draw(this->GetSprite());
}
