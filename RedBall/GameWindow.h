#include "GameMap.h"
#include "GameState.h"
#include "MainMenuState.h"

class GameWindow
{
private:
	sf::RenderWindow * window;
	std::stack<State*> states;

	bool IsOpen;
public:
	GameWindow();
	~GameWindow();

	void Update();
	void Render();

	bool Closed() const;
};

