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
	m_gamestate = GameState::ContextFreeMode;
	createWalls();
	m_sensitive.setVelocity(sf::Vector2f(200, 0));
	vertices[0] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
	vertices[1] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y - length), sf::Color::Red, sf::Vector2f(0, 10));
	vertices[2] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
	vertices[3] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + length), sf::Color::Red, sf::Vector2f(0, 10));
	vertices[4] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
	vertices[5] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
	vertices[6] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
	vertices[7] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
	vertices[8] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
	vertices[9] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 10));

	m_contextFree.setVelocity(m_maze.grid[34][18].getPosition());
	
	srand(time(NULL));
	m_wander.setVelocity(sf::Vector2f((rand() % 400) - 200, (rand() % 400) - 200));
	m_seek.setVelocity(sf::Vector2f(200, 0));
	m_seek.getDesiredVelocity() = getUnitVector(sf::Vector2f(m_maze.grid[34][18].getPosition() -m_seek.getPos()));
	m_seek.getSteering() = m_seek.getDesiredVelocity() - m_seek.getVel();

	if (!texture.loadFromFile("ASSETS/IMAGES/context-free.png"))
	{
		// error...
	}
	sprite.setTexture(texture);
	sprite.setPosition(400, 400);
	sprite.setScale(sf::Vector2f(0.3, 0.3));

	if (!texture2.loadFromFile("ASSETS/IMAGES/context-sensitive.png"))
	{
		// error...
	}
	sprite2.setTexture(texture2);
	sprite2.setPosition(400, 400);
	sprite2.setScale(sf::Vector2f(0.3, 0.3));

	if (!texture3.loadFromFile("ASSETS/IMAGES/seekWeb.jpg"))
	{
		// error...
	}
	sprite3.setTexture(texture3);
	sprite3.setPosition(400, 400);
	sprite3.setScale(sf::Vector2f(0.05, 0.05));

	if (!texture4.loadFromFile("ASSETS/IMAGES/wander.png"))
	{
		// error...
	}
	sprite4.setTexture(texture4);
	sprite4.setPosition(400, 400);
	sprite4.setScale(sf::Vector2f(0.15, 0.15));

	m_goalAI.setPosition(sf::Vector2f(1350, 200));
	m_goalAI.setSize(sf::Vector2f(50, 50));
	m_goalAI.setFillColor(sf::Color::Red);
	m_goalVelocity = sf::Vector2f(0, 100);

	

	m_font.loadFromFile("ASSETS/FONTS/ariblk.ttf");
	m_time.setPosition(1300, 10);
	m_time.setCharacterSize(24);
	m_time.setString("time: " + std::to_string(312.0f / 60));
	m_time.setFillColor(sf::Color::Black);
	m_time.setFont(m_font);
	
	resultMenu.setPosition(200, 200);
	resultMenu.setSize(sf::Vector2f(600, 600));
	resultMenu.setFillColor(sf::Color::Black);

	contextFreeTime.setPosition(300, 320);
	contextFreeTime.setFont(m_font);
	contextFreeTime.setFillColor(sf::Color::White);
	contextFreeTime.setCharacterSize(24);
	
	contextFreeExecution.setPosition(300, 360);
	contextFreeExecution.setFont(m_font);
	contextFreeExecution.setFillColor(sf::Color::White);
	contextFreeExecution.setCharacterSize(24);


	contextFreePathLength.setPosition(300, 400);
	contextFreePathLength.setFont(m_font);
	contextFreePathLength.setFillColor(sf::Color::White);
	contextFreePathLength.setCharacterSize(24);

	contextFreeCollision.setPosition(300, 440);
	contextFreeCollision.setFont(m_font);
	contextFreeCollision.setFillColor(sf::Color::White);
	contextFreeCollision.setCharacterSize(24);
	contextFreeCollision.setString("Number of Collisions: 2");

	modeString.setPosition(300, 270);
	modeString.setFont(m_font);
	modeString.setFillColor(sf::Color::White);
	modeString.setCharacterSize(24);
	modeString.setStyle(sf::Text::Underlined);

	wanderTime.setPosition(300, 320);
	wanderTime.setFont(m_font);
	wanderTime.setFillColor(sf::Color::White);
	wanderTime.setCharacterSize(24);

	wanderCollision.setPosition(300, 440);
	wanderCollision.setFont(m_font);
	wanderCollision.setFillColor(sf::Color::White);
	wanderCollision.setCharacterSize(24);

	wanderPathLength.setPosition(300, 400);
	wanderPathLength.setFont(m_font);
	wanderPathLength.setFillColor(sf::Color::White);
	wanderPathLength.setCharacterSize(24);

	wanderExecution.setPosition(300, 360);
	wanderExecution.setFont(m_font);
	wanderExecution.setFillColor(sf::Color::White);
	wanderExecution.setCharacterSize(24);

	seekTime.setPosition(300, 320);
	seekTime.setFont(m_font);
	seekTime.setFillColor(sf::Color::White);
	seekTime.setCharacterSize(24);

	seekExecution.setPosition(300, 360);
	seekExecution.setFont(m_font);
	seekExecution.setFillColor(sf::Color::White);
	seekExecution.setCharacterSize(24);

	seekPathLength.setPosition(300, 400);
	seekPathLength.setFont(m_font);
	seekPathLength.setFillColor(sf::Color::White);
	seekPathLength.setCharacterSize(24);

	seekCollision.setPosition(300, 440);
	seekCollision.setFont(m_font);
	seekCollision.setFillColor(sf::Color::White);
	seekCollision.setCharacterSize(24);


	sensitiveTime.setPosition(300, 320);
	sensitiveTime.setFont(m_font);
	sensitiveTime.setFillColor(sf::Color::White);
	sensitiveTime.setCharacterSize(24);

	sensitiveExecution.setPosition(300, 360);
	sensitiveExecution.setFont(m_font);
	sensitiveExecution.setFillColor(sf::Color::White);
	sensitiveExecution.setCharacterSize(24);

	sensitivePathLength.setPosition(300, 400);
	sensitivePathLength.setFont(m_font);
	sensitivePathLength.setFillColor(sf::Color::White);
	sensitivePathLength.setCharacterSize(24);

	sensitiveCollision.setPosition(300, 440);
	sensitiveCollision.setFont(m_font);
	sensitiveCollision.setFillColor(sf::Color::White);
	sensitiveCollision.setCharacterSize(24);


	if (!goalTexture.loadFromFile("ASSETS/IMAGES/goal.png"))
	{
		// error...
	}
	goalSprite.setTexture(goalTexture);
	goalSprite.setPosition(sf::Vector2f(m_goalAI.getPosition().x -10, m_goalAI.getPosition().y));
	goalSprite.setScale(0.5f, 0.5f);

	for (int i = 0; i < 4; i++)
	{
		scores[i].setPosition(300, 320 + i * 40);
		scores[i].setFont(m_font);
		scores[i].setFillColor(sf::Color::White);
		scores[i].setCharacterSize(24);
	}
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
	goalSprite.setPosition(sf::Vector2f(m_goalAI.getPosition().x-10, m_goalAI.getPosition().y));
	if (m_exitGame)
	{
		m_window.close(); 
	}
	if (m_contextFree.getPos().y > 650 && m_contextFree.getPos().y < 700)
	{
		if (distBools[2] == false)
		{
			executionStart = t_deltaTime.asSeconds();
		}
		m_contextFree.setVelocity(m_maze.grid[34][18].getPosition());
		if (m_gamestate == GameState::ContextFreeMode)
		{
			if (distBools[2] == false)
			{
				m_contextFree.calcPathLength();
				distBools[2] = true;
				executionEnd = t_deltaTime.asSeconds();
			}
		}
	}

	if (m_contextFree.getPos().y > 800)
	{
		m_contextFree.setVelocity(m_goalAI.getPosition());
		if (m_gamestate == GameState::ContextFreeMode)
		{
			if (distBools[0] == false)
			{
				m_contextFree.calcPathLength();
				distBools[0] = true;
			}
		}
	}

	m_contextFree.move(m_maze.grid[34][18].getPosition(), t_deltaTime);

	for (int i = 0; i < 20; i++)
	{
		if (calculateDistBetween(m_walls[i].getPos(), m_contextFree.getPos()) < 50.0f)
		{
			m_contextFree.setVelocityDown();
		}
		if (m_walls[i].getBody().getGlobalBounds().intersects(m_wander.getBody().getGlobalBounds()))
		{
			m_wander.setVelocity(sf::Vector2f(m_wander.getVel().x * -1, m_wander.getVel().y * -1));
			if (!doOnce)
			{
				wanderCollisionCount++;
				m_wander.calcPathLength();
				doOnce = true;
			}
		}
	}
	doOnce = false;

	if (calculateDistBetween(m_goalAI.getPosition(), m_contextFree.getPos()) < 50.0f && m_gamestate == GameState::ContextFreeMode)
	{
		m_contextFree.setMovingFalse();
		m_contextFree.calcPathLength();
		if (m_gamestate == GameState::ContextFreeMode)
		{
			if (distBools[1] == false)
			{
				m_contextFree.calcPathLength();
				distBools[1] = true;
			}
		}
		m_gamestate = GameState::ContextFreeResults;
	}
vertices[0] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
vertices[1] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y - length), sf::Color::Red, sf::Vector2f(0, 10));
vertices[2] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y), sf::Color::Red, sf::Vector2f(0, 0));
vertices[3] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width + length), sf::Color::Red, sf::Vector2f(0, 10));
vertices[4] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
vertices[5] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
vertices[6] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 0));
vertices[7] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width), sf::Color::Red, sf::Vector2f(0, 10));
vertices[8] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
vertices[9] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width + length), sf::Color::Green, sf::Vector2f(0, 10));
vertices[10] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
vertices[11] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width - length), sf::Color::Green, sf::Vector2f(0, 10));
vertices[12] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
vertices[13] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width - length, m_sensitive.getPos().y + width + length), sf::Color::Green, sf::Vector2f(0, 10));
vertices[14] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width, m_sensitive.getPos().y + width), sf::Color::Green, sf::Vector2f(0, 0));
vertices[15] = sf::Vertex(sf::Vector2f(m_sensitive.getPos().x + width + length, m_sensitive.getPos().y + width - length), sf::Color::Green, sf::Vector2f(0, 10));
if (m_gamestate == GameState::WanderMode)
{
	executionStart = t_deltaTime.asSeconds();
	m_wander.move(t_deltaTime);
	executionEnd = t_deltaTime.asSeconds();
}

if (m_wander.getBody().getPosition().y < 50)
{
	m_wander.setVelocity(sf::Vector2f(rand() % 400 - 200, rand() % 200 + 1));
	wanderCollisionCount++;
	m_wander.calcPathLength();
}
if (m_wander.getBody().getPosition().x < 50)
{
	m_wander.setVelocity(sf::Vector2f(rand() % 200 + 1, rand() % 400 - 200));
	wanderCollisionCount++;
	m_wander.calcPathLength();
}
if (m_wander.getBody().getPosition().y > 900)
{
	m_wander.setVelocity(sf::Vector2f(rand() % 400 - 200, rand() % 200 * -1));
	wanderCollisionCount++;
	m_wander.calcPathLength();
}
if (m_wander.getBody().getPosition().x > 1700)
{
	m_wander.setVelocity(sf::Vector2f(rand() % 200 * -1, rand() % 400 - 200));
	wanderCollisionCount++;
	m_wander.calcPathLength();
}

if ( m_wander.getPos().x > 1300 && calculateDistBetween(m_goalAI.getPosition(), m_wander.getPos()) < 600.0f)
{
	m_wander.setVelocity(sf::Vector2f(m_goalAI.getPosition() - m_wander.getPos()));
}

for (int i = 0; i < 3; i++)
{
	distBools[i] = false;
}
if (m_gamestate == GameState::SeekMode)
{
	m_seek.move(t_deltaTime);
	if (moving)
	{
		m_seek.setVelocity(sf::Vector2f(m_seek.getVel().x, m_seek.getVel().y + force));
	}
}



if (m_seek.getBody().getGlobalBounds().intersects(m_goalAI.getGlobalBounds()))
{
	moving = false;
	m_seek.setPosition();
	m_gamestate = GameState::SeekModeResults;
	m_seek.calcPathLength();
}
sprite.setPosition(m_contextFree.getPos().x, m_contextFree.getPos().y - 20);
sprite2.setPosition(m_sensitive.getPos().x-45, m_sensitive.getPos().y - 20);
sprite3.setPosition(m_seek.getPos().x, m_seek.getPos().y - 20);
sprite4.setPosition(m_wander.getPos().x, m_wander.getPos().y - 20);


m_goalAI.setPosition(m_goalAI.getPosition() + m_goalVelocity * t_deltaTime.asSeconds());
if (m_goalAI.getPosition().y >= 799 && m_goalAI.getPosition().x < 1599)
{
	m_goalVelocity = sf::Vector2f(100, 0);
}
else if (m_goalAI.getPosition().y >= 799 && m_goalAI.getPosition().x >= 1599)
{
	m_goalVelocity = sf::Vector2f(0, -100);
}
else if (m_goalAI.getPosition().y <= 200 && m_goalAI.getPosition().x >= 1599)
{
	m_goalVelocity = sf::Vector2f(-100, 0);
}
else if (m_goalAI.getPosition().y <= 200 && m_goalAI.getPosition().x <= 1350)
{
	m_goalVelocity = sf::Vector2f(0, 100);
}

if (m_gamestate == GameState::ContextFreeMode)
{
	m_contextFree.update();
	counter++;
	m_time.setString("Time: " + std::to_string(counter / 60.0f));
}
if (m_gamestate == GameState::ContextFreeResults)
{
	contextFreeExecution.setString("Average execution time: " + std::to_string(executionStart - executionEnd / counter));
	contextFreeTime.setString("Time taken was: " + std::to_string(counter / 60.0f));
	contextFreePathLength.setString("Path length was: " + std::to_string(m_contextFree.getPathLength() ));
	modeString.setString("Context-free results:");
	contextFreeScore = (counter / 60.0f) + m_contextFree.getPathLength() + 400;
	resultsTimer++;

	if (resultsTimer == 300)
	{
		m_gamestate = GameState::WanderMode;
		counter = 0;
	}
}


if (m_gamestate == GameState::WanderMode)
{
	resultsTimer = 0;
	m_time.setString("Time: " + std::to_string(counter / 60.0f));
	counter+=2;
	
	if (calculateDistBetween(m_goalAI.getPosition(), m_wander.getPos()) < 50.0f)
	{
		m_wander.calcPathLength();
		m_gamestate = GameState::WanderModeResults;
	}
}


if (m_gamestate == GameState::WanderModeResults)
{
	wanderScore = (counter / 60.0f) + m_wander.getPathLength() + (100 * wanderCollisionCount);
	modeString.setString("Wander results:");
	wanderTime.setString("Time taken was: " + std::to_string(counter / 60.0f));
	wanderCollision.setString("Number of collisions: " + std::to_string(wanderCollisionCount /2 + 1));
	wanderPathLength.setString("Path length was: " + std::to_string(m_wander.getPathLength()));
	wanderExecution.setString("Average execution time: " + std::to_string(executionStart - executionEnd / counter));
	resultsTimer++;

	if (resultsTimer == 300)
	{
		m_gamestate = GameState::SeekMode;
		counter = 0;
	}
}

if (m_gamestate == GameState::SeekMode)
{
	
	executionStart = t_deltaTime.asSeconds();
	m_time.setString("Time: " + std::to_string(counter / 60.0f));
	counter++;
	std::cout << std::to_string(m_seek.getPos().y) << std::endl;
	if (m_seek.getPos().y >= 700 && m_seek.getPos().x < 800)
	{
		m_seek.getDesiredVelocity() = getUnitVector(sf::Vector2f(m_goalAI.getPosition() - m_seek.getPos()));
		m_seek.getSteering() = m_seek.getDesiredVelocity() - m_seek.getVel();
		m_seek.setVelocity(sf::Vector2f(200, 0));
		m_seek.calcPathLength();
	}
	if (m_seek.getPos().y >= 900 && m_seek.getPos().x < 1200 && m_seek.getPos().x > 1000)
	{
		
		m_seek.calcPathLength();
		m_seek.setVelocity(sf::Vector2f(m_goalAI.getPosition() - m_seek.getPos()));
	}
	else if (m_seek.getPos().y >= 900 && m_seek.getPos().x > 1200)
	{
		m_seek.calcPathLength();
		force = 0.0f;
		m_seek.setSteering();
		m_seek.setVelocity(sf::Vector2f(m_goalAI.getPosition() - m_seek.getPos()));
	} 

	if (m_seek.getPos().x > m_goalAI.getPosition().x)
	{
		m_seek.setVelocity(sf::Vector2f(getUnitVector(m_goalAI.getPosition() - m_seek.getPos())));
	}

	resultsTimer = 0;
	executionEnd = t_deltaTime.asSeconds();
	if (counter / 60.0f == 6)
	{
		force = 0.0f;
	}
}


if (m_gamestate == GameState::SeekModeResults)
{
	seekScore = (counter / 60.0f) + m_seek.getPathLength() + 0;
	modeString.setString("Seek results:");
	seekTime.setString("Time taken was:  " + std::to_string(counter / 60.0f));
	seekExecution.setString("Average execution time: " + std::to_string(executionStart - executionEnd / counter));
	seekCollision.setString("Number of collisions: " + std::to_string(0));
	seekPathLength.setString("Path length was: " + std::to_string(m_seek.getPathLength()));

	resultsTimer++;

	if (resultsTimer == 300)
	{
		m_gamestate = GameState::ContextSensitiveMode;
		counter = 0;
	}
}

if (m_gamestate == GameState::ContextSensitiveMode)
{
	executionStart = t_deltaTime.asSeconds();
	m_time.setString("Time: " + std::to_string(counter / 60.0f));
	counter++;
	if (counter / 60.0f >= 3.4 && m_sensitive.getPos().x < 1100)
	{
		m_sensitive.setVelocity(sf::Vector2f(200, 50));
		m_sensitive.calcPathLength();
	}
	if (m_sensitive.getPos().x > 1300)
	{
		m_sensitive.setVelocity(sf::Vector2f( getUnitVector(m_goalAI.getPosition() - m_sensitive.getPos())));
		m_sensitive.calcPathLength();
		moving = false;
	}
	if (m_sensitive.getBody().getGlobalBounds().intersects(m_goalAI.getGlobalBounds()))
	{
		m_sensitive.calcPathLength();
		m_gamestate = GameState::ContextSensitiveResults;
	}
	m_sensitive.move(t_deltaTime);
	executionEnd = t_deltaTime.asSeconds();
	resultsTimer = 0;
}


if (m_gamestate == GameState::ContextSensitiveResults)
{
	contextSensitiveScore = (counter / 60.0f) + m_sensitive.getPathLength() + 0;
	modeString.setString("ContextSensitive results:");
	sensitiveTime.setString("Time taken was:  " + std::to_string(counter / 60.0f));
	sensitiveExecution.setString("Average execution time: " + std::to_string(executionStart - executionEnd / counter));
	sensitiveCollision.setString("Number of collisions: " + std::to_string(0));
	sensitivePathLength.setString("Path length was: " + std::to_string(m_sensitive.getPathLength()));

	resultsTimer++;

	if(resultsTimer == 300)
	{
		m_gamestate = GameState::Comparison;
	}
}

if (m_gamestate == GameState::Comparison)
{
	modeString.setString("Scores of each AI:");
	scores[0].setString("ContextFree Score: " + std::to_string(contextFreeScore));
	scores[1].setString("Wander Score: " + std::to_string(wanderScore));
	scores[2].setString("Seek Score: " + std::to_string(seekScore));
	scores[3].setString("ContextSensitive Score: " + std::to_string(contextSensitiveScore));
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
	for (int i = 0; i < 108; i++)
	{
		m_window.draw(m_outerWalls->getBody());
	}

	m_window.draw(m_goalAI);
	m_window.draw(goalSprite);

	if (m_gamestate == GameState::ContextFreeMode)
	{
		m_window.draw(m_contextFree.getBody());
		m_window.draw(sprite);
		m_window.draw(m_time);
	}
	else if (m_gamestate == GameState::ContextFreeResults)
	{
		m_window.draw(resultMenu);
		m_window.draw(contextFreeTime);
		m_window.draw(contextFreeExecution);
		m_window.draw(contextFreeCollision);
		m_window.draw(modeString);
		m_window.draw(contextFreePathLength);
	}
	else if (m_gamestate == GameState::SeekMode)
	{
		m_window.draw(m_seek.getBody());
		m_window.draw(sprite3);
	}
	else if (m_gamestate == GameState::SeekModeResults)
	{
		m_window.draw(resultMenu);
		m_window.draw(modeString);
		m_window.draw(seekTime);
		m_window.draw(seekExecution);
		m_window.draw(seekPathLength);
		m_window.draw(seekCollision);
	}
	else if (m_gamestate == GameState::WanderMode)
	{
		m_window.draw(m_wander.getBody());
		m_window.draw(sprite4);
	}
	else if (m_gamestate == GameState::WanderModeResults)
	{
		m_window.draw(resultMenu);
		m_window.draw(modeString);
		m_window.draw(wanderTime);
		m_window.draw(wanderCollision);
		m_window.draw(wanderPathLength);
		m_window.draw(wanderExecution);
	}
	else if (m_gamestate == GameState::ContextSensitiveMode)
	{
		m_window.draw(m_sensitive.getBody());
		m_window.draw(vertices, numOfVertices, sf::Lines);
		m_window.draw(sprite2);
	}
	else if (m_gamestate == GameState::ContextSensitiveResults)
	{
		m_window.draw(resultMenu);
		m_window.draw(modeString);
		m_window.draw(sensitiveCollision);
		m_window.draw(sensitiveExecution);
		m_window.draw(sensitivePathLength);
		m_window.draw(sensitiveTime);
	}
	else if (m_gamestate == GameState::Comparison)
	{
		m_window.draw(resultMenu);
		m_window.draw(modeString);
		for (int i = 0; i < 4; i++)
		{
			m_window.draw(scores[i]);
		}
	}
	m_window.draw(m_time);
	m_window.display();
}

sf::Vector2f Game::getUnitVector(sf::Vector2f vel)
{
	float unit = sqrt(vel.x * vel.x + vel.y * vel.y);
	vel = sf::Vector2f(vel.x / unit * 200.0f , vel.y / unit * 200.0f);
	return vel;
}

