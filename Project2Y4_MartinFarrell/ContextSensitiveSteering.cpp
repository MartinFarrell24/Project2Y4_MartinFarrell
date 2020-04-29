#include"ContextSensitiveSteering.h"

ContextSensitiveSteering::ContextSensitiveSteering()
{
	m_pos = sf::Vector2f(100, 105);
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

void ContextSensitiveSteering::move(sf::Time time)
{
	m_pos = m_pos + m_vel * time.asSeconds();
	m_body.setPosition(m_pos);
}

void ContextSensitiveSteering::setVelocity(sf::Vector2f dir)
{
	m_vel = dir;
}

void ContextSensitiveSteering::calcPathLength()
{
	distTravelled += sqrt(((prevPos.x - m_pos.x) * (prevPos.x - m_pos.x)) + ((prevPos.y - m_pos.y) * (prevPos.y - m_pos.y)));
	prevPos = m_pos;
}

float ContextSensitiveSteering::getPathLength()
{
	return distTravelled;
}
