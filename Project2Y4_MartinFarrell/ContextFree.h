#pragma once
#include<SFML/Graphics.hpp>

class ContextFree
{
public:
	ContextFree();
	~ContextFree();
	sf::CircleShape getBody();
	sf::Vector2f getPos();
	void setVelocity(sf::Vector2f goal);
	void setVelocityDown();
	void move(sf::Vector2f goal, sf::Time time);
	void setMovingFalse();

private:
	sf::CircleShape m_body;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	sf::Vector2f m_prevVel;
	float speed = 500;
	bool moving = true;
};
