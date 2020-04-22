#pragma once

#include"SFML/Graphics.hpp"
class Seek
{
public:
	Seek();
	~Seek();
	void setVelocity(sf::Vector2f newVel);
	void move(sf::Time time);
	sf::CircleShape getBody();
	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getSteering();
	sf::Vector2f getDesiredVelocity();

private:
	sf::CircleShape m_body;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	sf::Vector2f desiredVelocity;
	sf::Vector2f steering;
	float speed = 250;
};
