#pragma once
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "Square.h"

extern std::vector<Square> G_STATICOBJECTS;

struct CarState {
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);
	
	//must add car position to corner to get it's global position
	sf::Vector2f corners[4];
	sf::Vector2f position = sf::Vector2f(0.0f, 0.0f);

	float rotDeg = 0.0f;
	float rotRad = 0.0f;
};

class Car
{
	static const float c_length;
	static const float c_height;
	static const float c_rotationSpeed;
	static const float c_acceleration;
	static const float c_brakeForce;
	static const float c_frictionForce;
	static const float c_dbg_slideSpeed;
	static const float c_maxMomentum;

public:
	Car(sf::Vector2f pos);
	
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(const sf::Vector2f& dir, float dtMilli);
	void Update(sf::RenderWindow& window,float dtTimeMilli);

	~Car();

private:
	sf::RectangleShape shape;


	CarState newState;
	CarState currState;

	void ApplyFriction(float dtTimeMilli);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);

	bool CollisionDetected();
};

