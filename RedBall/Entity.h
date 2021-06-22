#include "Block.h"
#include "Spike.h"
#include "Coin.h"
#include "Flag.h"

class Entity
{
private:
	sf::Texture entityTexture;
	sf::Sprite entitySprite;

	sf::Vector2f position;
	sf::Vector2f size;
	float speed;
	float maxSpeed;
public:
	Entity(sf::Vector2f _position, int _maxSpeed, int _w, int _h);
	~Entity();

	void SetTexture(sf::Texture texture);

	virtual void Move(int dir) = 0;
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow * target) = 0;

	sf::Vector2f GetPosition() const;
	sf::Sprite GetSprite() const;
	float GetSpeed() const;
	float GetMaxSpeed() const;
	sf::Vector2f GetSize() const;

	void SetSpeed(float val);
	void SetPostion(sf::Vector2f _newPosition);
};

