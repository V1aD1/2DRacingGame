#pragma once

#include <SFML/Graphics.hpp>

#include "EventHandler.h"

class VariableEntity {
public:
	virtual void Update(sf::RenderWindow& window, float dtTimeMilli, EventHandler& handler) = 0;

};
