#pragma once
#include"SFML/Graphics.hpp"
class Wander
{
public:
	Wander();
	~Wander();
	void setVelocity(sf::Vector2f newVel);
	void move(sf::Time time);
	sf::CircleShape getBody();
	sf::Vector2f getPos();
	sf::Vector2f getVel();

private:
	sf::CircleShape m_body;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	float speed = 250;
};
