#include <iostream>

#include "include/CarGraphicsComponent.h"
#include "include/Entity.h"

CarGraphicsComponent::CarGraphicsComponent(sf::Shape* shape) : GraphicsComponent(shape){
	for (int i = 0; i < 4; i++) {
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		cornerCircles.push_back(circle);
	}
}

CarGraphicsComponent::~CarGraphicsComponent(){}

void CarGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window)
{
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
		m_shape->setPosition(entity.GetPosition());
		window.draw(*m_shape);
	}

	DBG_DrawCorners(entity, window);
}

void CarGraphicsComponent::HandleCollision(sf::Vector2f otherEntityMomentum)
{
	;
}

void CarGraphicsComponent::DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window) {
	auto entityCorners = entity.GetWorldCorners();
	if (entityCorners && entityCorners->size() == 4) {
		for (int i = 0; i < 4; i++) {
			cornerCircles[i].setPosition((*entityCorners)[i]);
			window.draw(cornerCircles[i]);
		}
	}
}
