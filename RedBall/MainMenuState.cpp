#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow * window, std::stack<State*>* _states)
	:State(window, _states)
{
	this->startBtn = new Button(300, 300, 200, 50, &this->font, "Start", 36);
	this->quitBtn = new Button(300, 400, 200, 50, &this->font, "Quit", 36);

	this->music = new sf::Music();
	this->music->openFromFile("music/MainMenu.wav");
	this->music->setLoop(true);
	this->music->play();
}

void MainMenuState::Update()
{
	this->UpdateMousePositions();
	this->startBtn->Update(this->mousePosWindow);
	this->quitBtn->Update(this->mousePosWindow);

	if (this->startBtn->isPressed())
	{
		this->music->stop();
		this->states->push(new GameState(this->window, this->states));
	}

	if (this->quitBtn->isPressed())
	{
		this->states->top()->EndState();
	}
}

void MainMenuState::UpdateInput()
{
}

void MainMenuState::Render()
{
	sf::Text text(sf::String("Red Ball"), this->font, 72);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f((800 - text.getGlobalBounds().width) / 2, 150));
	this->window->draw(text);

	this->startBtn->Render(*this->window);
	this->quitBtn->Render(*this->window);
}