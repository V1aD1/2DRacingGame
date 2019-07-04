#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class InputComponent;

static class EntityFactory
{
public:

	static Entity* CreateSquare(float sideLen, sf::Vector2f pos, float rotDeg);
	static Entity* CreatePlayer1(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText);
	static Entity* CreatePlayer2(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText);
	static Entity* CreateParticle(float alphaReductionRate);

private:
	static Entity* CreateCar(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText, InputComponent* inputCom);

private:
	static const float c_car_length;
	static const float c_car_width;
};

