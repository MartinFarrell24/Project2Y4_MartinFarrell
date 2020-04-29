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
	void calculateDanger(sf::Vector2f posOther);
	void calculateDesire(sf::Vector2f goal);
	void updateRadials();
	void setVelocity(sf::Vector2f dir);
	void calcPathLength();
	float getPathLength();

private:
	float speed = 150;
	sf::CircleShape m_body;
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	float m_danger[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float m_desire[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	int direction = 2;

	float width = 25;
	float length = 50;
	static const int numOfVertices = 16;
	sf::Vertex vertices[numOfVertices];
	sf::Vector2f prevPos;
	float distTravelled = 0.0;
};
