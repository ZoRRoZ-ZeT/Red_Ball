#include "Game.h"

Game::Game()
{
	this->window = new GameWindow();
}

Game::~Game()
{
	this->window = nullptr;
}

void Game::Start()
{
	while (!this->window->Closed())
	{
		this->window->Update();
	}
}
