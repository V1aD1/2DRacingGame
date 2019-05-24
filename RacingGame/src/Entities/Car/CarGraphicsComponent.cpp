#include <iostream>

#include "../../Entities/Car/CarGraphicsComponent.h"
#include "../Entity.h"

CarGraphicsComponent::CarGraphicsComponent(sf::Shape* shape) : GraphicsComponent(shape){
	for (int i = 0; i < 4; i++) {
		auto circle = sf::CircleShape(circleRad, 4);
		circle.setOrigin(circleRad, circleRad);
		cornerCircles.push_back(circle);
	}
}

CarGraphicsComponent::~CarGraphicsComponent(){}

void CarGraphicsComponent::Update(Entity& entity, sf::RenderWindow& window, float dtTimeMilli)
{
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
		m_shape->setPosition(entity.GetPosition());
		window.draw(*m_shape);
	}

	DBG_DrawCorners(entity, window);
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
