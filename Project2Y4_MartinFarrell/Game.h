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
#include"Gamestate.h"
#include<string.h>

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
	GameState m_gamestate;
	sf::RectangleShape m_goalAI;
	sf::Vector2f m_goalVelocity;
	sf::Text m_time;
	sf::Font m_font;
	float counter = 0.0f;

	sf::Texture goalTexture;
	sf::Sprite goalSprite;


	sf::RectangleShape resultMenu;
	sf::Text modeString;
	sf::Text contextFreeTime;
	sf::Text contextFreeExecution;
	sf::Text contextFreePathLength;
	sf::Text contextFreeCollision;
	sf::Text wanderTime;
	sf::Text wanderExecution;
	sf::Text wanderPathLength;
	sf::Text wanderCollision;
	sf::Text seekTime;
	sf::Text seekExecution;
	sf::Text seekPathLength;
	sf::Text seekCollision;
	sf::Text sensitiveTime;
	sf::Text sensitiveExecution;
	sf::Text sensitivePathLength;
	sf::Text sensitiveCollision;

	int wanderCollisionCount = 0;
	bool distBools[3];
	float executionStart;
	float executionEnd;
	float resultsTimer = 0;
	bool doOnce = false;
	float force = 2.4f;

	int contextFreeScore =0;
	int wanderScore=0;
	int seekScore=0;
	int contextSensitiveScore=0;
	sf::Text scores[4];

	int count = 0;
};

#endif // !GAME_HPP

