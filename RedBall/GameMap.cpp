#include "GameMap.h"

GameMap::GameMap(int * _time)
	:timePlayed(_time)
{

	std::fstream fs;
	fs.open("levels/level1.mymap");

	while (!fs.eof())
	{
		std::string temp;
		std::getline(fs, temp);
		if (temp[0] != '[')
			continue;
		
		temp[0] = ' ';
		std::stringstream ss(temp);

		std::string val;
		std::getline(ss, val, ',');
		int posX = atoi(val.c_str());
		std::getline(ss, val, ',');
		int posY = atoi(val.c_str());
		std::getline(ss, val, ',');
		std::string path = val;
		std::getline(ss, val, ']');
		std::string type = val;
		if(type == "block")
			obstacles.push_back(new Block(sf::Vector2f(posX * 100, posY * 100), sf::Vector2f(100, 100), "img/" + path));
		else if(type == "spike")
			obstacles.push_back(new Spike(sf::Vector2f(posX * 100, posY * 100 + 50), sf::Vector2f(100, 50), "img/" + path));
		else if(type == "coin")
			obstacles.push_back(new Coin(sf::Vector2f(posX * 100 + 25, posY * 100 + 25), sf::Vector2f(50, 50), "img/" + path));
		else if (type == "flag")
			obstacles.push_back(new Flag(sf::Vector2f(posX * 100, posY * 100), sf::Vector2f(100, 100), "img/" + path));

	}

	fs.close();

	this->score = 0;

	this->player = new Player(sf::Vector2f(600, 500), 10, 50, 50, &obstacles,&score);

	this->font = new sf::Font();
	this->font->loadFromFile("fonts/Dosis-Light.ttf");

	this->lostText = new sf::Text(sf::String("You are Lose!"), *font,60);
	this->lostText->setFillColor(sf::Color::Red);
	this->lostText->setPosition(sf::Vector2f((800 - this->lostText->getGlobalBounds().width) / 2, (600 - this->lostText->getGlobalBounds().height) / 2 - 70));

	this->winText = new sf::Text(sf::String("You are Win!"), *font, 60);
	this->winText->setFillColor(sf::Color::Green);
	this->winText->setPosition(sf::Vector2f((800 - this->lostText->getGlobalBounds().width) / 2, (600 - this->lostText->getGlobalBounds().height) / 2 - 70));

}

GameMap::~GameMap()
{
	this->player = nullptr;
}

void GameMap::Render(sf::RenderWindow * target)
{
	if (!this->player->GetWin())
	{
		this->player->Render(target);
		for (auto i : obstacles)
		{
			if (abs(i->GetSprite().getGlobalBounds().left - this->player->GetPosition().x) < 650.f &&
				abs(i->GetSprite().getGlobalBounds().top - this->player->GetPosition().y) < 450.f)
			{
				i->Render(target);
			}
		}

		if (this->player->IsDead())
		{
			target->setView(target->getDefaultView());
			target->draw(*this->lostText);
		}
	}
	else
	{
		target->setView(target->getDefaultView());
		target->draw(*this->winText);

		sf::Text infoText(sf::String("Score: " + std::to_string(this->score)), *this->font);
		infoText.setPosition(sf::Vector2f((800 - infoText.getGlobalBounds().width) / 2, this->winText->getPosition().y + this->winText->getGlobalBounds().height + 100));
		target->draw(infoText);

		std::string time = std::to_string(*this->timePlayed / 60) + ":";
		if (*this->timePlayed % 60 < 10)
		{
			time += "0" + std::to_string(*this->timePlayed % 60);
		}
		else
		{
			time += std::to_string(*this->timePlayed % 60);
		}
		infoText.setString("Time remained: " + time);
		infoText.setPosition(sf::Vector2f((800 - infoText.getGlobalBounds().width) / 2, this->winText->getPosition().y + this->winText->getGlobalBounds().height + 200));
		target->draw(infoText);
	}
}
Player* GameMap::GetPlayer()
{
	return this->player;
}

std::vector<Obstacle*> GameMap::GetObstacles()
{
	return this->obstacles;
}

int GameMap::GetScore() const
{
	return this->score;
}
