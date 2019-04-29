#include "include/ParticleGraphicsComponent.h"
#include "include/Entity.h"

ParticleGraphicsComponent::ParticleGraphicsComponent() : GraphicsComponent()
{
	//creating a simple pixel for particles
	auto shape = new sf::CircleShape(5.0f, 4);
	shape->setOrigin(0.5f, 0.5f);
	shape->setFillColor(sf::Color::White);

	m_shape = shape;
}


ParticleGraphicsComponent::~ParticleGraphicsComponent()
{
}

void ParticleGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window)
{
	//simple particle, so only update position, NOT rotation
	if (m_shape) {
		m_shape->setPosition(entity.GetPosition());
		window.draw(*m_shape);
	}
}

void ParticleGraphicsComponent::HandleCollision(sf::Vector2f otherEntityMomentum)
{
	;
}