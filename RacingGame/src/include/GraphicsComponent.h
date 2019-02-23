#pragma once
#include <SFML/Graphics.hpp>
#include "ConvexEntity.h"

//forward declaration
class Entity;

class GraphicsComponent
{
public:
	GraphicsComponent(sf::Shape* shape);
	~GraphicsComponent();


	void Update(const Entity& entity, sf::RenderWindow & window);

private:
	sf::Shape* m_shape;
};

