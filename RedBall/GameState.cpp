#include "GameState.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow * window, std::stack<State*>* _states)
	:State(window, _states)
{
	this->currentView = new sf::View(sf::FloatRect(-400, 0, 800, 600));

	this->scoreText = new sf::Text();
	this->scoreText->setFont(font);
	this->scoreText->setFillColor(sf::Color::White);

	this->healthText = new sf::Text();
	this->healthText->setFont(font);
	this->healthText->setFillColor(sf::Color::White);

	this->timeText = new sf::Text();
	this->timeText->setFont(font);
	this->timeText->setFillColor(sf::Color::White);

	this->currentTime.restart();

	this->map = new GameMap(&this->timeElapsed);

	this->music = new sf::Music();
	this->music->openFromFile("music/Game.wav");
	this->music->setLoop(true);
	this->music->play();
}


void GameState::Update()
{
	this->map->GetPlayer()->Update();
	this->scoreText->setString("Score: " + std::to_string(this->map->GetScore()));
	this->healthText->setString("Health: " + std::to_string(this->map->GetPlayer()->GetHealth()));


	if (!this->map->GetPlayer()->IsDead() && !this->map->GetPlayer()->GetWin())
	{
		this->timeElapsed = 180 - (int)this->currentTime.getElapsedTime().asSeconds();
		if (this->timeElapsed == 0)
			this->map->GetPlayer()->Lose();
		std::string time = std::to_string(this->timeElapsed / 60) + ":";
		if (this->timeElapsed % 60 < 10)
			time += "0" + std::to_string(this->timeElapsed % 60);
		else
			time += std::to_string(this->timeElapsed % 60);

		this->timeText->setString(time);
	}
	this->healthText->setPosition(sf::Vector2f(0, 0));
	this->scoreText->setPosition(sf::Vector2f((800 - this->scoreText->getGlobalBounds().width) / 2, 0));
	this->timeText->setPosition(sf::Vector2f(800 - this->timeText->getGlobalBounds().width, 0));
}

void GameState::UpdateInput()
{
	if (!this->map->GetPlayer()->IsDead() && !this->map->GetPlayer()->GetWin())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->map->GetPlayer()->Move(1);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->map->GetPlayer()->Move(-1);
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->map->GetPlayer()->Move(0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->map->GetPlayer()->Jump();
		}
	}
	else
	{
		this->music->stop();
		for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
			{
				this->states->top()->EndState();
			}
		}
	}
}

void GameState::Render()
{

	this->window->clear(sf::Color(135, 206, 235));

	this->window->setView(*this->currentView);

	this->map->Render(this->window);

	this->currentView = new sf::View(sf::FloatRect(this->map->GetPlayer()->GetPosition().x - 400, this->map->GetPlayer()->GetPosition().y - 300, 800, 600));

	this->window->setView(this->window->getDefaultView());

	this->window->draw(*this->healthText);
	this->window->draw(*this->scoreText);
	this->window->draw(*this->timeText);
}
