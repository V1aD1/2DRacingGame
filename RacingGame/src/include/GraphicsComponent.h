#pragma once
#include <SFML/Graphics.hpp>

//forward declaration
class ConvexEntity;

class GraphicsComponent
{
public:
	GraphicsComponent();
	~GraphicsComponent();


	void Update(const ConvexEntity& convexEntity, sf::RenderWindow & window, float dtTimeMilli);

};

