#pragma once
#include"SFML/Graphics.hpp"

class ContextSensitiveSteering
{
public:
	ContextSensitiveSteering();
	~ContextSensitiveSteering();
	sf::CircleShape getBody();
	sf::Vector2f getPos();


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

};
