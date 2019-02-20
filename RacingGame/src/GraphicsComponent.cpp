#include "include/ConvexEntity.h"
#include "include/GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
}

void GraphicsComponent::Update(const ConvexEntity& convexEntity, sf::RenderWindow & window)
{
	float circleRad = 2.0f;

	window.draw(*(convexEntity.GetShape()));
	for (auto corner : convexEntity.GetWorldCorners())
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corner);
		window.draw(circle);
	}

}

GraphicsComponent::~GraphicsComponent()
{
}

