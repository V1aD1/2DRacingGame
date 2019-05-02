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

	virtual void Update(const Entity& entity, sf::RenderWindow& window, float dtTimeMilli) = 0;
	virtual void HandleCollision(sf::Vector2f otherEntityMomentum) = 0;
	
	//todo make functions that don't need to be virtual as not virtual!
	virtual sf::Shape* GetShape();
	virtual void Enable();

protected:
	sf::Shape* m_shape;
};

