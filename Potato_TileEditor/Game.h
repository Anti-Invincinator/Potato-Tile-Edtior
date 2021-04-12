#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:

	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;         

	std::map<std::string, int> supportedKeys;   //string for key, int for key value from sfml

	float gridSize;

	//Initialization Functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();


public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void UpdateSFMLEvents();
	void Update();

	//Render
	void Render();

	//Core
	void Run();
};

#endif // !GAME_H



