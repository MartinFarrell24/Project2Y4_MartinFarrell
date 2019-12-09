#pragma once
#include"SFML/Graphics.hpp"

class ContextSensitiveSteering
{
public:
	ContextSensitiveSteering();
	~ContextSensitiveSteering();
	sf::CircleShape getBody();
	sf::Vector2f getPos();

	void move(sf::Time time);
	void checkIfDanger();
	void updateVelocity(sf::Vector2f goal);
	void updateDanger();
	void setGoalFoundTrue();
	void setMovingFalse();

private:
	float speed = 150;
	sf::CircleShape m_body;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	float m_danger[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float m_desire[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	sf::Vector2f m_direction[8];
	int direction = 2;

	bool goalFound = false;
	bool moving = true;
};
