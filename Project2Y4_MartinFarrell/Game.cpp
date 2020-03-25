/// <summary>
/// @author Martin Farrell
/// @date Oct 2019
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1800U, 1000U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	createWalls();
	
	//vertices[0] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
	//vertices[1] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y - length), sf::Color::Red, sf::Vector2f(0, 10));
	//vertices[2] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
	//vertices[3] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + length), sf::Color::Red, sf::Vector2f(0, 10));
	//vertices[4] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
	//vertices[5] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
	vertices[6] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
	vertices[7] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
	//vertices[8] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
	//vertices[9] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 10));
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
void Game::createWalls()
{
	for (int i = 3; i < 13; i++)
	{
		m_walls[i - 3].setPos(m_maze.grid[15][i].getPosition());
	}

	for (int i = 6; i < 16; i++)//wall
	{
		m_walls[i + 4].setPos(m_maze.grid[24][i].getPosition());
	}

	for (int i = 0; i < 36; i++)
	{
		m_outerWalls[i].setPos(m_maze.grid[i][0].getPosition());
	}
	for (int i = 36; i < 72; i++)
	{
		m_outerWalls[i].setPos(m_maze.grid[i-36][19].getPosition());
	}
	for (int i = 0; i < 18; i++)
	{
		m_outerWalls[i + 72].setPos(m_maze.grid[0][i + 1].getPosition());
	}
	for (int i = 0; i < 18; i++)
	{
		m_outerWalls[i + 90].setPos(m_maze.grid[0][i + 1].getPosition());
	}
}
float Game::calculateDistBetween(sf::Vector2f pointOne, sf::Vector2f pointTwo)
{
	float distance = ((pointOne.x - pointTwo.x) * (pointOne.x - pointTwo.x)) + ((pointOne.y - pointTwo.y) * (pointOne.y - pointTwo.y));
	return sqrt(distance);

}
bool Game::rayCastWall()
{
	const float x1 = m_walls[0].getPos().x;
	const float y1 = m_walls[0].getPos().y;
	const float x2 = m_walls[10].getPos().x;
	const float y2 = m_walls[10].getPos().y;

	const float x3 = vertices[6].position.x;
	const float y3 = vertices[6].position.y;
	const float x4 = vertices[6].position.x + dir.x;
	const float y4 = vertices[6].position.y + dir.y;

	const float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denominator == 0)
	{
		return false;
	}

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
	const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x2)) / denominator;

	if (t > 0 && t < 1 && u > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close(); 
	}
	count++;
	if (count == numOfFrames)
	{
		m_contextFree.setVelocity(m_maze.grid[34][18].getPosition());
		count = 0;
	}

	m_contextFree.move(m_maze.grid[34][18].getPosition(), t_deltaTime);

	for (int i = 0; i < 20; i++)
	{
		if (calculateDistBetween(m_walls[i].getPos(), m_contextFree.getPos()) < 50.0f)
		{
			m_contextFree.setVelocityDown();
		}
	}

	if (calculateDistBetween(m_maze.grid[34][18].getPosition(), m_contextFree.getPos()) < 50.0f)
	{
		m_contextFree.setMovingFalse();
	}
	//vertices[0] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
	//vertices[1] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y - length), sf::Color::Red, sf::Vector2f(0, 10));
	//vertices[2] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
	//vertices[3] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width + length), sf::Color::Red, sf::Vector2f(0, 10));
	//vertices[4] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
	//vertices[5] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
	vertices[6] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
	vertices[7] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
	//vertices[8] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
	//vertices[9] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width + length), sf::Color::Green, sf::Vector2f(0, 10));
	//vertices[10] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
	//vertices[11] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width - length), sf::Color::Green, sf::Vector2f(0, 10));
	//vertices[12] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
	//vertices[13] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width + length), sf::Color::Green, sf::Vector2f(0, 10));
	//vertices[14] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
	//vertices[15] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width - length), sf::Color::Green, sf::Vector2f(0, 10));

	std::cout << rayCastWall();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear();
	
	for (int row = 0; row < 36; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			m_window.draw(m_maze.grid[row][col]);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		m_window.draw(m_walls[i].getBody());
	}
	for (int i = 0; i < 108; i++)
	{
		m_window.draw(m_outerWalls->getBody());
	}

	m_window.draw(m_contextFree.getBody());
	m_window.draw(m_sensitive.getBody());
	m_window.draw(vertices, numOfVertices, sf::Lines);
	m_window.display();
}

