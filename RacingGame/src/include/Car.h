#pragma once
#include <SFML/Graphics.hpp>

class Car
{
public:
	Car();
	Car(float posX, float posY);
	
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Update(sf::RenderWindow& window,float dtTimeMilli);

	~Car();

private:
	sf::RectangleShape shape;
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	float maxSpeed = 200.0f;
	float rotationSpeed = 180.0f;
	float acceleration = 120.0f;
	float currentSpeed = 0.0f;
};

