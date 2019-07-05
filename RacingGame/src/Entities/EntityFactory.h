#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class InputComponent;

static class EntityFactory
{
public:
	static Entity* CreateStaticCollisionObject(sf::Vector2f startPos, float startRotInDeg, sf::Vector2f scale, sf::Texture& text);
	static Entity* CreateDecorativeObject(sf::Vector2f startPos, float startRotInDeg, sf::Vector2f scale, sf::Texture& text);
	static Entity* CreatePlayer1(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText);
	static Entity* CreatePlayer2(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText);
	static Entity* CreateParticle(float alphaReductionRate);
	static Entity* CreateGrassTerrain(float sideLen, sf::Vector2f startPos, sf::Vector2f scale);
	static Entity* CreateDirtTerrain(float sideLen, sf::Vector2f startPos, sf::Vector2f scale);

	static Entity* DBG_CreateSquare(float sideLen, sf::Vector2f startPos, float startRotInDeg);

private:
	static Entity* CreateCar(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText, InputComponent* inputCom);

private:
	static const float c_car_length;
	static const float c_car_width;
};

