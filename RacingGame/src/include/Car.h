#pragma once
#include <SFML/Graphics.hpp>

class Car
{
public:
	Car();
	Car(sf::Vector2f pos);
	
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(const sf::Vector2f& dir, float dtMilli);
	void Update(sf::RenderWindow& window,float dtTimeMilli);

	~Car();

private:
	sf::RectangleShape shape;
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f corners[4];
	sf::Vector2f currPos = sf::Vector2f(0.0f, 0.0f);

	float maxMomentum = 0.3f;

	float rotDeg = 0.0f;
	float rotRad = 0.0f;
	float rotationSpeed = 180.0f;
	float acceleration = 0.25f;
	float brakeForce = 0.1f;
	float frictionForce = 0.1f;
	float dbg_slideSpeed = 150.0f;

	void ApplyFriction(float dtTimeMilli);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);

	static const float length;
	static const float height;
};

