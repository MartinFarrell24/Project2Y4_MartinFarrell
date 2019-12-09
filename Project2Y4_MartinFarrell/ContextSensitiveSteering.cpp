#include"ContextSensitiveSteering.h"

ContextSensitiveSteering::ContextSensitiveSteering()
{
	m_pos = sf::Vector2f(500, 805);
	m_body.setPointCount(3);
	m_body.setFillColor(sf::Color::Magenta);
	m_body.setPosition(sf::Vector2f(m_pos));
	m_body.setRadius(50);

	m_direction[0] = sf::Vector2f(0, -speed);
	m_direction[1] = sf::Vector2f(speed, -speed);
	m_direction[2] = sf::Vector2f(speed, 0);
	m_direction[3] = sf::Vector2f(speed, speed);
	m_direction[4] = sf::Vector2f(0, speed);
	m_direction[5] = sf::Vector2f(-speed, speed);
	m_direction[6] = sf::Vector2f(-speed, 0);
	m_direction[7] = sf::Vector2f(-speed, -speed);

	m_vel = m_direction[0];
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
	if (moving)
	{
		m_pos = m_pos + m_vel * time.asSeconds();
		m_body.setPosition(m_pos);
	}
}

void ContextSensitiveSteering::checkIfDanger()
{
	if (m_danger[direction] > 0)
	{
		direction++;
		if (direction > 7)
		{
			direction = 0;
		}
	}
}

void ContextSensitiveSteering::updateVelocity(sf::Vector2f goal)
{
	if (!goalFound)
	{
		m_vel = m_direction[direction];
	}
	else
	{
		m_vel = goal - m_pos;
		float unit = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
		m_vel = sf::Vector2f(m_vel.x / unit * speed, m_vel.y / unit * speed);
	}
}

void ContextSensitiveSteering::updateDanger()
{
	m_danger[direction] = 1;

	for (int i = 0; i < 8; i++)
	{
		if (!i == direction)
		{
			m_danger[i] = 0;
		}
	}
}

void ContextSensitiveSteering::setGoalFoundTrue()
{
	goalFound = true;
}

void ContextSensitiveSteering::setMovingFalse()
{
	moving = false;
}
