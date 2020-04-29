#include"Wander.h"

Wander::Wander()
{
	m_pos = sf::Vector2f(100, 105);
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
	m_pos = m_pos + m_vel * 2.0f * time.asSeconds();
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

void Wander::calcPathLength()
{
	distTravelled += sqrt(((prevPos.x - m_pos.x) * (prevPos.x - m_pos.x)) + ((prevPos.y - m_pos.y) * (prevPos.y - m_pos.y)));
	prevPos = m_pos;
}

float Wander::getPathLength()
{
	return distTravelled;
}
