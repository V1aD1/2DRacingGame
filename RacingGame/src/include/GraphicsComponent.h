#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class GraphicsComponent
{
public:
	GraphicsComponent(sf::Shape* shape);
	virtual ~GraphicsComponent();

	virtual void Update(const Entity& entity, sf::RenderWindow & window) = 0;

protected:
	sf::Shape* m_shape;
};

