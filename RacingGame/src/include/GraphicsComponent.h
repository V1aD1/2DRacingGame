#pragma once
#include <SFML/Graphics.hpp>
#include "ConvexEntity.h"

//forward declaration
class ConvexEntity;

class GraphicsComponent
{
public:
	GraphicsComponent(ConvexEntity* convexEnt);
	~GraphicsComponent();


	void Update(sf::RenderWindow & window);

private:
	ConvexEntity * m_convexEnt;
};

