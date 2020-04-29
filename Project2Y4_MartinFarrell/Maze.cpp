#include"Maze.h"

Maze::Maze()
{
	for (int row = 0; row < 36; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			grid[row][col].setPosition(50 * row, 50 * col);
			grid[row][col].setFillColor(sf::Color::Blue);
			grid[row][col].setOutlineColor(sf::Color::White);
			grid[row][col].setOutlineThickness(1.0f);
			grid[row][col].setSize(sf::Vector2f(50, 50));
		}
	}

	for (int i = 0; i < 36; i++)
	{
		grid[i][0].setFillColor(sf::Color::Green);
		grid[i][19].setFillColor(sf::Color::Green);
	}
	for (int i = 0; i < 20; i++)
	{
		grid[0][i].setFillColor(sf::Color::Green);
		grid[35][i].setFillColor(sf::Color::Green);
	}
}

Maze::~Maze()
{
}

void Maze::render(sf::RenderWindow)
{
}
