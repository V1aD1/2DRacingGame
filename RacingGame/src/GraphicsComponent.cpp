#include "include/ConvexEntity.h"
#include "include/GraphicsComponent.h"


GraphicsComponent::GraphicsComponent(sf::Shape* shape)
{
	m_shape = shape;
}

void GraphicsComponent::Update(const Entity& entity, sf::RenderWindow & window)
{
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
	}

	float circleRad = 2.0f;

	window.draw(*m_shape);
	for (auto corner : entity.GetWorldCorners())
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

