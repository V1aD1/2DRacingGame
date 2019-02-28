#include "include/SquareGraphicsComponent.h"
#include "include/Entity.h"


SquareGraphicsComponent::SquareGraphicsComponent(sf::Shape* shape) : GraphicsComponent(shape) {}

SquareGraphicsComponent::~SquareGraphicsComponent(){}

//overridden Update() method from GraphicsComponent
void SquareGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window){
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
		m_shape->setPosition(entity.GetPosition());
	}

	float circleRad = 8.0f;

	window.draw(*m_shape);

	for (auto corner : *(entity.GetWorldCorners()))
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corner);
		window.draw(circle);
	}
}
