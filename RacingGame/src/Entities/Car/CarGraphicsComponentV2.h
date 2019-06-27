#pragma once
#include "../../Components/GraphicsComponent.h"

class CarGraphicsComponentV2 : public GraphicsComponent
{
private:
	float circleRad = 2.0f;
	std::vector<sf::CircleShape> cornerCircles;

private:
	void DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window);

public:
	CarGraphicsComponentV2(sf::Sprite* sprite);
	~CarGraphicsComponentV2();

	void Update(Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
};

