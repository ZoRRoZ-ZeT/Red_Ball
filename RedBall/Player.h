#pragma once
#include "Entity.h"
class Player :
	public Entity
{
private:
	float jumpSpeed;
	float jumpAcceleration;

	float acceleration;

	int direction;

	bool isMoving;
	bool isJumping;
	bool isHitted;
	bool isDied;

	bool onGoal;

	int health;

	std::vector<Obstacle*>* obstacles;
	int * score;
public:
	Player(sf::Vector2f _position, int _maxSpeed, int _w, int _h, std::vector<Obstacle*>* _obstacles, int * _score);
	~Player();

	bool BlockForward();
	bool OnGround();

	void Update();
	void Render(sf::RenderWindow * target);

	void Jump();
	void Move(int dir);

	void Hit();
	void Collect(Obstacle* coin);
	void Win();
	void Lose();

	int GetDirection() const;
	int GetHealth() const;
	int GetWin() const;

	bool IsDead() const;
};

