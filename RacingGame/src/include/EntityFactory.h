#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class InputComponent;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* CreateSquare(float sideLen, sf::Vector2f pos, float rotDeg);
	Entity* CreatePlayer1(sf::Vector2f pos);
	Entity* CreatePlayer2(sf::Vector2f pos);



private:
	Entity* CreateCar(sf::Vector2f pos, sf::Color color, InputComponent* inputCom);

private:
	static const float c_car_length;
	static const float c_car_height;
};

