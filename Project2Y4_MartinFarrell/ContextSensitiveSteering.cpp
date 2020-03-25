#include"ContextSensitiveSteering.h"

ContextSensitiveSteering::ContextSensitiveSteering()
{
	m_pos = sf::Vector2f(700, 405);
	m_body.setPointCount(3);
	m_body.setFillColor(sf::Color::Magenta);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setRadius(25);
}

ContextSensitiveSteering::~ContextSensitiveSteering()
{
}

sf::CircleShape ContextSensitiveSteering::getBody()
{
	return m_body;
}

sf::Vector2f ContextSensitiveSteering::getPos()
{
	return m_pos;
}
