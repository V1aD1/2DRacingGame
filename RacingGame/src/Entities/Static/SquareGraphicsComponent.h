#pragma once
#include <array>
#include <SFML/Graphics.hpp>

#include "../../Components/GraphicsComponent.h"

class SquareGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 8.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	SquareGraphicsComponent(sf::Shape* shape);
	~SquareGraphicsComponent();
	void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
};

