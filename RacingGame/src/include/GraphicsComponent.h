#pragma once
#include <SFML/Graphics.hpp>
#include "ConvexEntity.h"

//forward declaration
class Entity;

class GraphicsComponent
{
public:
	GraphicsComponent(Entity* convexEnt);
	~GraphicsComponent();


	void Update(sf::RenderWindow & window);

private:
	Entity * m_convexEnt;
};

