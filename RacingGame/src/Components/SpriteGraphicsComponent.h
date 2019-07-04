#pragma once
#include "GraphicsComponent.h"

class SpriteGraphicsComponent : public GraphicsComponent
{
private:
	float circleRad = 2.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	SpriteGraphicsComponent(sf::Sprite* sprite);
	~SpriteGraphicsComponent();

	void Update(Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
};

