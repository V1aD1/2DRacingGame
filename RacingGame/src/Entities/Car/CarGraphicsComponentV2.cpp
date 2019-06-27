#include <iostream>

#include "CarGraphicsComponentV2.h"
#include "../Entity.h"


CarGraphicsComponentV2::CarGraphicsComponentV2(sf::Sprite* sprite) : GraphicsComponent(sprite)
{
	for (int i = 0; i < 4; i++) {
		auto circle = sf::CircleShape(circleRad, 4);
		circle.setOrigin(circleRad, circleRad);
		cornerCircles.push_back(circle);
	}
}

CarGraphicsComponentV2::~CarGraphicsComponentV2()
{
}

void CarGraphicsComponentV2::Update(Entity& entity, sf::RenderWindow& window, float dtTimeMilli)
{
	if (m_sprite) {
		m_sprite->setRotation(entity.GetRotationInDegrees());
		m_sprite->setPosition(entity.GetPosition());
		window.draw(*m_sprite);
	}

	DBG_DrawCorners(entity, window);
}

void CarGraphicsComponentV2::DBG_DrawCorners(const Entity& entity, sf::RenderWindow& window)
{
	auto entityCorners = entity.GetWorldCorners();
	if (entityCorners && entityCorners->size() == 4) {
		for (int i = 0; i < 4; i++) {
			cornerCircles[i].setPosition((*entityCorners)[i]);
			window.draw(cornerCircles[i]);
		}
	}
}
