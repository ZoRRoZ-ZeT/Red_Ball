#pragma once
#include "State.h"
#include "GameMap.h"

class GameState :
	public State
{
private:
	sf::View * currentView;

	sf::Text* scoreText;
	sf::Text* healthText;
	sf::Text* timeText;

	sf::Clock currentTime;
	int timeElapsed;

	GameMap * map;

	sf::Music* music;
public:
	GameState(sf::RenderWindow* window, std::stack<State*>* _states);

	void Update();
	void UpdateInput();

	void Render();
};

