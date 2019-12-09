#include"Maze.h"

Maze::Maze()
{
	for (int row = 0; row < 36; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			grid[row][col].setPosition(100 * row, 100 * col);
			grid[row][col].setFillColor(sf::Color::Blue);
			grid[row][col].setOutlineColor(sf::Color::White);
			grid[row][col].setOutlineThickness(2.0f);
			grid[row][col].setSize(sf::Vector2f(100, 100));
		}
	}


	grid[1][1].setFillColor(sf::Color::Magenta);//start square
	grid[34][18].setFillColor(sf::Color::Red);//end square

	//for (int i = 3; i < 13; i++)//wall
	//{
	//	grid[15][i].setFillColor(sf::Color::Green);
	//}
	

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
