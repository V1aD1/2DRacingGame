#include <iostream>

#include "include/CarGraphicsComponent.h"
#include "include/Entity.h"

CarGraphicsComponent::CarGraphicsComponent(sf::Shape* shape) : GraphicsComponent(shape){}

CarGraphicsComponent::~CarGraphicsComponent(){}

void CarGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window)
{
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
		m_shape->setPosition(entity.GetPosition());
		window.draw(*m_shape);
	}

	float circleRad = 2.0f;

	auto entityCorners = entity.GetWorldCorners();
	if (entityCorners) {
		int i = 0;
		for (auto corner : *entityCorners)
		{
			auto circle = sf::CircleShape(circleRad);
			circle.setOrigin(circleRad, circleRad);
			circle.setPosition(corner);
			window.draw(circle);
			i++;
			if (i == 2)
				break;
		}
	}
}
