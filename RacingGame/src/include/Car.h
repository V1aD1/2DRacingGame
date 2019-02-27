#pragma once
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Car : public Entity
{
public:
	Car(sf::Vector2f pos);
	~Car();

private:
	static const float c_length;
	static const float c_height;
};

