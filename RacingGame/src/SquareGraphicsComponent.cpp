#include "include/SquareGraphicsComponent.h"
#include "include/Entity.h"


SquareGraphicsComponent::SquareGraphicsComponent(sf::Shape* shape, std::array<sf::Vector2f, 4> worldCorners) : GraphicsComponent(shape) {
	m_shape = shape;
	m_worldCorners = worldCorners;
}


SquareGraphicsComponent::~SquareGraphicsComponent()
{
}

//overridden Update() method from GraphicsComponent
void SquareGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window)
{
	if (m_shape) {
		m_shape->setRotation(entity.GetRotationInDegrees());
	}

	float circleRad = 8.0f;

	window.draw(*m_shape);

	for (auto corner : m_worldCorners)
	{
		auto circle = sf::CircleShape(circleRad);
		circle.setOrigin(circleRad, circleRad);
		circle.setPosition(corner);
		window.draw(circle);
	}
}
