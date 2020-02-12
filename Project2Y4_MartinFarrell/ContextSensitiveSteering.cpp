#include"ContextSensitiveSteering.h"

ContextSensitiveSteering::ContextSensitiveSteering()
{
	m_pos = sf::Vector2f(500, 805);
	m_body.setPointCount(3);
	m_body.setFillColor(sf::Color::Magenta);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setRadius(50);
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

void ContextSensitiveSteering::setInitialVel(sf::Vector2f goalPos)
{
	sf::Vector2f temp = goalPos - m_pos;
	float unit = sqrt((temp.x * temp.x) + (temp.y * temp.y));
	m_vel = sf::Vector2f(temp.x / unit, temp.y / unit) * speed;
}

void ContextSensitiveSteering::move(sf::Time time)
{
	if (moving)
	{
		m_pos = m_pos + m_vel * time.asSeconds();
		m_body.setPosition(m_pos);
	}
}

void ContextSensitiveSteering::calculateDanger()
{

}

void ContextSensitiveSteering::updateVelocity(sf::Vector2f goal)
{
	/*if (!goalFound)
	{
		m_vel = m_direction[direction];
	}
	else
	{
		m_vel = goal - m_pos;
		float unit = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
		m_vel = sf::Vector2f(m_vel.x / unit * speed, m_vel.y / unit * speed);
	}*/
}

void ContextSensitiveSteering::updateDanger()
{

}

void ContextSensitiveSteering::setGoalFoundTrue()
{
	goalFound = true;
}

void ContextSensitiveSteering::setMovingFalse()
{
	moving = false;
}
