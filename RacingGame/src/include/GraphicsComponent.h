#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class GraphicsComponent
{
public:
	GraphicsComponent();
	GraphicsComponent(sf::Shape* shape);

	//todo figure out virtual destructors and whether they should exist
	virtual ~GraphicsComponent();

	virtual void Update(const Entity& entity, sf::RenderWindow& window) = 0;
	virtual void HandleCollision(sf::Vector2f otherEntityMomentum) = 0;

protected:
	sf::Shape* m_shape;
};

