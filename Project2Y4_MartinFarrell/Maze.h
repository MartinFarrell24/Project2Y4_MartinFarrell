#ifndef MAZE_HPP
#define MAZE_HPP
#include<SFML/Graphics.hpp>

class Maze
{
public:
	Maze();
	~Maze();
	void render(sf::RenderWindow);
	sf::RectangleShape grid[36][20];

private:
	
};
#endif // !MAZE_HPP