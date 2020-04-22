#include "Seek.h"

Seek::Seek()
{
	m_pos = sf::Vector2f(1100, 105);
	m_body.setPointCount(3);
	m_body.setFillColor(sf::Color::Cyan);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setRadius(25);
}

Seek::~Seek()
{
}

void Seek::setVelocity(sf::Vector2f newVel)
{
	m_vel = newVel;
	float unit = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
	m_vel = sf::Vector2f(m_vel.x / unit * speed, m_vel.y / unit * speed);
}

void Seek::move(sf::Time time)
{
	m_pos = m_pos + m_vel * time.asSeconds();
	m_body.setPosition(m_pos);
}

sf::CircleShape Seek::getBody()
{
	return m_body;
}

sf::Vector2f Seek::getPos()
{
	return m_pos;
}

sf::Vector2f Seek::getVel()
{
	return m_vel;
}

sf::Vector2f Seek::getSteering()
{
	return steering;
}

sf::Vector2f Seek::getDesiredVelocity()
{
	return sf::Vector2f();
}
