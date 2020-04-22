#include"Wander.h"

Wander::Wander()
{
	m_pos = sf::Vector2f(1700, 105);
	m_body.setPointCount(3);
	m_body.setFillColor(sf::Color::Red);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setRadius(25);
}

Wander::~Wander()
{
}

void Wander::setVelocity(sf::Vector2f newVel)
{
	m_vel = newVel;
	float unit = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
	m_vel = sf::Vector2f(m_vel.x / unit * speed, m_vel.y / unit * speed);
}

void Wander::move(sf::Time time)
{
	m_pos = m_pos + m_vel * time.asSeconds();
	m_body.setPosition(m_pos);
}

sf::CircleShape Wander::getBody()
{
	return m_body;
}

sf::Vector2f Wander::getPos()
{
	return m_pos;
}

sf::Vector2f Wander::getVel()
{
	return m_vel;
}
