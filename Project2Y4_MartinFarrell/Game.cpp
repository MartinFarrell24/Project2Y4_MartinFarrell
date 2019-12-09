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
	m_window{ sf::VideoMode{ 3600U, 2000U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	createWalls();
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
}
float Game::calculateDistBetween(sf::Vector2f pointOne, sf::Vector2f pointTwo)
{
	float distance = ((pointOne.x - pointTwo.x) * (pointOne.x - pointTwo.x)) + ((pointOne.y - pointTwo.y) * (pointOne.y - pointTwo.y));
	return sqrt(distance);

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

	m_window.draw(m_contextFree.getBody());
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

}
