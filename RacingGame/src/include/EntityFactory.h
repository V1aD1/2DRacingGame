#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* CreateSquare(float sideLen, sf::Vector2f pos, float rotDeg);
	Entity* CreateCar(sf::Vector2f pos);

private:
	static const float c_car_length;
	static const float c_car_height;
};

