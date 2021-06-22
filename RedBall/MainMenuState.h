#pragma once
#include "State.h"
#include "GameState.h"

class MainMenuState :
	public State
{
private:
	Button* startBtn;
	Button* quitBtn;

	sf::Music* music;

public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* _states);

	void Update();
	void UpdateInput();

	void Render();
};

