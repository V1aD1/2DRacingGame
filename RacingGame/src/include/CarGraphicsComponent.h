#pragma once
//#include <SFML/Graphics.hpp>

#include "GraphicsComponent.h"

class CarGraphicsComponent : public GraphicsComponent
{
public:
	CarGraphicsComponent(sf::Shape* shape);
	virtual ~CarGraphicsComponent();

	virtual void Update(const Entity& entity, sf::RenderWindow & window);
};

