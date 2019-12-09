#include"Wall.h"

Wall::Wall()
{
	m_body.setSize(sf::Vector2f(width, width));
	m_body.setFillColor(sf::Color::Green);
}

Wall::~Wall()
{
}

void Wall::setPos(sf::Vector2f newPos)
{
	m_pos = newPos;
	m_body.setPosition(m_pos);
}

sf::RectangleShape Wall::getBody()
{
	return m_body;
}

sf::Vector2f Wall::getPos()
{
	return m_pos;
}
