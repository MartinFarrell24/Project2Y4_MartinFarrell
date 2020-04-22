/// <summary>
/// author Martin Farrell Oct 2019
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include"Maze.h"
#include"ContextFree.h"
#include"Wall.h"
#include"ContextSensitiveSteering.h"
#include"Wander.h"
#include<ctime>
#include"Seek.h"

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
	bool rayCastWall();
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	sf::Vector2f getUnitVector(sf::Vector2f vel);

private:
	Maze m_maze;
	float width = 25;
	float length = 50;
	sf::Vector2f dir = sf::Vector2f(1000, 0);
	ContextFree m_contextFree;
	ContextSensitiveSteering m_sensitive;
	Wall m_walls[20];
	Wall m_outerWalls[108];
	Wall m_bottomWall[18];
	int count = 0;
	int numOfFrames = 30;
	static const int numOfVertices = 16;
	sf::Vertex vertices[numOfVertices];

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	Wander m_wander;
	Seek m_seek;
	sf::Vector2f vecTowardsGoal;
	bool moving = true;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture texture2;
	sf::Sprite sprite2;
	sf::Texture texture3;
	sf::Sprite sprite3;
	sf::Texture texture4;
	sf::Sprite sprite4;
};

#endif // !GAME_HPP

