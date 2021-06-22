#include "Player.h"

Player::Player(sf::Vector2f _position, int _maxSpeed, int _w, int _h, std::vector<Obstacle*>* _obstacles, int * _score)
	:Entity(_position, _maxSpeed, _w, _h), score(_score)
{
	this->acceleration = 0;
	this->direction = 0;
	this->isMoving = false;
	this->obstacles = _obstacles;
	this->isHitted = false;
	this->health = 3;
	this->isDied = false;
	this->onGoal = false;
}

Player::~Player()
{
}

bool Player::BlockForward()
{
	for (auto i : *obstacles)
	{

		if (abs(i->GetSprite().getGlobalBounds().left - this->GetPosition().x) > 650.f &&
			abs(i->GetSprite().getGlobalBounds().top - this->GetPosition().y) > 450.f)
		{
			continue;
		}

		std::string type = typeid(*i).name();

		//  Up Side
		if (this->GetPosition().x + this->GetSize().x > i->GetSprite().getPosition().x
			&& this->GetPosition().x < i->GetSprite().getPosition().x + i->GetSprite().getGlobalBounds().width
			&& this->GetPosition().y - this->jumpSpeed < i->GetSprite().getPosition().y + i->GetSprite().getGlobalBounds().height
			&& this->GetPosition().y - this->jumpSpeed > i->GetSprite().getPosition().y)
		{
			if (type == "class Spike")
			{
				this->Hit();
			}
			else if (type == "class Coin")
			{
				this->Collect(i);
			}
			else if (type == "class Block")
			{
				this->SetPostion(sf::Vector2f(this->GetPosition().x, i->GetSprite().getPosition().y + i->GetSprite().getGlobalBounds().height));
				this->jumpSpeed = 0;
				this->jumpAcceleration *= -1;
			}
			return true;
		}

		// Left Side
		if (this->GetPosition().x + this->GetSpeed() + this->GetSize().x > i->GetSprite().getPosition().x
			&& this->GetPosition().x + this->GetSpeed() + this->GetSize().x < i->GetSprite().getPosition().x + i->GetSprite().getGlobalBounds().width
			&& this->GetPosition().y + this->GetSize().y > i->GetSprite().getPosition().y + 5.f
			&& this->GetPosition().y < i->GetSprite().getPosition().y + i->GetSprite().getGlobalBounds().height - 5.f)
		{
			if (type == "class Spike")
			{
				this->Hit();
			}
			else if (type == "class Coin")
			{
				this->Collect(i);
			}
			else if (type == "class Flag")
			{
				this->Win();
			}
			else if (type == "class Block")
			{
				this->SetPostion(sf::Vector2f(i->GetSprite().getPosition().x - this->GetSize().x, this->GetPosition().y));
				this->SetSpeed(0);
				this->acceleration = 0;
			}
			return true;
		}

		// Right Side
		if (this->GetPosition().x + this->GetSpeed() < i->GetSprite().getPosition().x + i->GetSprite().getGlobalBounds().width
			&& this->GetPosition().x + this->GetSpeed() + this->GetSize().x > i->GetSprite().getPosition().x
			&& this->GetPosition().y + this->GetSize().y > i->GetSprite().getPosition().y + 5.f
			&& this->GetPosition().y < i->GetSprite().getPosition().y + i->GetSprite().getGlobalBounds().height - 5.f)
		{
			if (type == "class Spike")
			{
				this->Hit();
			}
			else if (type == "class Coin")
			{
				this->Collect(i);
			}
			else if (type == "class Flag")
			{
				this->Win();
			}
			else if (type == "class Block")
			{
				this->SetPostion(sf::Vector2f(i->GetSprite().getPosition().x + i->GetSprite().getGlobalBounds().width, this->GetPosition().y));
				this->SetSpeed(0);
				this->acceleration = 0;
			}
			
			return true;
		}
	}
	return false;
}

bool Player::OnGround()
{
	bool OnBlock = false;
	for (auto i : *obstacles)
	{
		if (abs(i->GetSprite().getGlobalBounds().left - this->GetPosition().x) > 650.f &&
			abs(i->GetSprite().getGlobalBounds().top - this->GetPosition().y) > 450.f)
		{
			continue;
		}

		std::string type = typeid(*i).name();
		if (type != "class Block")
			continue;

		if (this->GetPosition().y + this->GetSize().y - this->jumpSpeed >= i->GetSprite().getPosition().y
			&& this->GetPosition().y <= i->GetSprite().getPosition().y + i->GetSprite().getGlobalBounds().height - 20.f
			&& this->GetPosition().x + this->GetSize().x > i->GetSprite().getPosition().x
			&& this->GetPosition().x < i->GetSprite().getPosition().x + i->GetSprite().getGlobalBounds().width)
		{
			OnBlock = true;
			this->SetPostion(sf::Vector2f(this->GetPosition().x, i->GetSprite().getPosition().y - this->GetSize().y));
			this->jumpSpeed = 0;
			this->jumpAcceleration = 0;
			if(isJumping)
				isJumping = false;
			if (isHitted)
				isHitted = false;
		}
	}
	if (!OnBlock)
	{
		isJumping = true;
		this->jumpAcceleration += 0.02f;
		this->jumpSpeed -= this->jumpAcceleration;

		this->SetPostion(sf::Vector2f(this->GetPosition().x, this->GetPosition().y - this->jumpSpeed));
	}

	return OnBlock;
}

void Player::Update()
{
	if (!isDied)
	{
		OnGround();

		if (this->isMoving || abs(this->GetSpeed()) > 0)
		{
			if (this->direction != 0 && !isHitted)
			{
				if (this->GetSpeed() != 0 && (this->direction != this->GetSpeed() / abs(this->GetSpeed())))
				{
					if (this->acceleration > 0.f)
						this->acceleration -= 0.05f;
					else
						this->acceleration = 0.f;

					this->SetSpeed(this->GetMaxSpeed() * this->acceleration * this->GetSpeed() / abs(this->GetSpeed()));
				}
				else
				{
					if (this->acceleration < 1.f)
						this->acceleration += 0.03;
					else
						this->acceleration = 1.f;

					this->SetSpeed(this->GetMaxSpeed() * this->acceleration * this->direction);
				}
			}
			else
			{
				if (this->acceleration > 0.f)
					this->acceleration -= 0.05f;
				else
					this->acceleration = 0.f;

				if (this->GetSpeed() != 0)
					this->SetSpeed(this->GetMaxSpeed() * this->acceleration * this->GetSpeed() / abs(this->GetSpeed()));
			}
		}

		this->BlockForward();
		this->SetPostion(sf::Vector2f(this->GetPosition().x + this->GetSpeed(), this->GetPosition().y));
	}
}

void Player::Render(sf::RenderWindow * target)
{
	sf::CircleShape TestShape(this->GetSize().x / 2);
	TestShape.setPosition(this->GetPosition());
	TestShape.setFillColor(sf::Color::Red);
	target->draw(TestShape);
}

void Player::Jump()
{
	if (!isJumping)
	{
		this->isJumping = true;
		this->jumpSpeed = 10.f;
	}
}

void Player::Move(int dir)
{
	this->direction = dir;
	if (dir != 0)
		this->isMoving = true;
	else
		this->isMoving = false;
}

void Player::Hit()
{
	isHitted = true;
	this->acceleration = 2;
	if(this->GetSpeed() > 0)
		this->SetSpeed(this->GetMaxSpeed() * (-1));
	else
		this->SetSpeed(this->GetMaxSpeed());

	this->jumpSpeed = 7.5f;
	this->jumpAcceleration = 0;
	
	this->health--;
	if (this->health == 0)
		this->Lose();
}

void Player::Collect(Obstacle* obstacle)
{
	auto it = std::find(obstacles->begin(), obstacles->end(), obstacle);
	obstacles->erase(it);
	*this->score += 5;
}

void Player::Win()
{
	this->onGoal = true;
}

void Player::Lose()
{
	this->isDied = true;
}

int Player::GetDirection() const
{
	return this->direction;
}

int Player::GetHealth() const
{
	return this->health;
}

int Player::GetWin() const
{
	return this->onGoal;
}

bool Player::IsDead() const
{
	return this->isDied;
}
