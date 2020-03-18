#pragma once
#include"SFML/Graphics.hpp"
class Wall
{
public:
	Wall();
	~Wall();
	void setPos(sf::Vector2f newPos);
	sf::RectangleShape getBody();
	sf::Vector2f getPos();

private:
	sf::Vector2f m_pos;
	float width = 50.0f;
	sf::RectangleShape m_body;
};
