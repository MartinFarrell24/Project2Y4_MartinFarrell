#include"ContextFree.h"

ContextFree::ContextFree()
{
	m_pos = sf::Vector2f(100, 105);
	prevPos = m_pos;
	m_body.setPointCount(3);
	m_body.setFillColor(sf::Color::Yellow);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setRadius(25);
}

ContextFree::~ContextFree()
{
}

sf::CircleShape ContextFree::getBody()
{
	return m_body;
}

sf::Vector2f ContextFree::getPos()
{
	return m_pos;
}

void ContextFree::setVelocity(sf::Vector2f goal)
{
	m_vel = goal - m_pos;
	float unit = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
	m_vel = sf::Vector2f(m_vel.x / unit * speed, m_vel.y / unit * speed);
}

void ContextFree::setVelocityDown()
{
	m_pos.x -= 50;
	m_body.setPosition(m_pos);
	m_vel = sf::Vector2f(0, 200);
}

void ContextFree::move(sf::Vector2f goal, sf::Time time)
{
	if (moving)
	{
		m_pos = m_pos + m_vel * time.asSeconds();
		m_body.setPosition(m_pos);
	}
}

void ContextFree::setMovingFalse()
{
	moving = false;
}

void ContextFree::update()
{
	count++;
}

float ContextFree::getCount()
{
	return count;
}

void ContextFree::calcPathLength()
{
	distTravelled += sqrt(((prevPos.x - m_pos.x) * (prevPos.x - m_pos.x)) + ((prevPos.y - m_pos.y) * (prevPos.y - m_pos.y)));
	prevPos = m_pos;
}

float ContextFree::getPathLength()
{
	return distTravelled;
}
