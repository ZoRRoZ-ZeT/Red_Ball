#include "State.h"

State::State(sf::RenderWindow * window, std::stack<State*>* _states)
	:window(window)
{
	this->states = _states;
	this->font.loadFromFile("fonts/Dosis-Light.ttf");
}

void State::UpdateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

const bool & State::GetQuit() const
{
	return this->quit;
}

void State::EndState()
{
	this->quit = true;
}
