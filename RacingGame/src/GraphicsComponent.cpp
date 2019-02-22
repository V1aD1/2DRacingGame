#include "include/ConvexEntity.h"
#include "include/GraphicsComponent.h"


GraphicsComponent::GraphicsComponent(ConvexEntity* convexEnt)
{
	m_convexEnt = convexEnt;
}

void GraphicsComponent::Update(sf::RenderWindow & window)
{
	float circleRad = 2.0f;

	window.draw(*(m_convexEnt->GetShape()));
	for (auto corner : m_convexEnt->GetWorldCorners())
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

