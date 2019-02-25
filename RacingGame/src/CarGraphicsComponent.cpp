#include <iostream>

#include "include/CarGraphicsComponent.h"
#include "include/Entity.h"

CarGraphicsComponent::CarGraphicsComponent(sf::Shape* shape) : GraphicsComponent(shape){}

//todo may not be necessary
CarGraphicsComponent::~CarGraphicsComponent()
{
}

void CarGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window)
{
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
		m_shape->setPosition(entity.GetPosition());
	}

	float circleRad = 2.0f;

	window.draw(*m_shape);

	auto entityCorners = entity.GetWorldCorners();

	if (entityCorners) {
		for (auto corner : *entityCorners)
		{
			auto circle = sf::CircleShape(circleRad);
			circle.setOrigin(circleRad, circleRad);
			circle.setPosition(corner);
			window.draw(circle);
		}
	}
}
