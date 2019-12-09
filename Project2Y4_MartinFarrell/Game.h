/// <summary>
/// author Martin Farrell Oct 2019
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include"Maze.h"
#include"ContextFree.h"
#include"Wall.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	void createWalls();
	float calculateDistBetween(sf::Vector2f pointOne, sf::Vector2f pointTwo);

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	Maze m_maze;
	ContextFree m_contextFree;
	Wall m_walls[20];



	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

