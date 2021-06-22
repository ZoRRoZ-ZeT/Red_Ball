#pragma once
#include "Player.h"

class GameMap
{
private:
	std::vector<Obstacle*> obstacles;
	Player * player;

	sf::Font* font;
	sf::Text* lostText;
	sf::Text* winText;

	int score;
	int * timePlayed;

public:
	GameMap(int * _time);
	~GameMap();

	void Render(sf::RenderWindow * target);

	Player* GetPlayer();
	std::vector<Obstacle*> GetObstacles();

	int GetScore() const;
};

