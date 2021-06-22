#include "GameWindow.h"

GameWindow::GameWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Red Ball");
	this->window->setFramerateLimit(60);
	
	this->IsOpen = true;

	this->states.push(new MainMenuState(this->window, &this->states));
}

void GameWindow::Update()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || this->states.top()->GetQuit())
		{
			this->window->close();
			this->IsOpen = false;
		}

		this->states.top()->UpdateInput();

		
	}

	this->states.top()->Update();


	this->Render();
}

void GameWindow::Render()
{
	this->window->clear();

	this->states.top()->Render();

	this->window->display();
}

bool GameWindow::Closed() const
{
	return !this->IsOpen;
}
