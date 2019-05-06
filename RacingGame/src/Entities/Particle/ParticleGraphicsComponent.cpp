#include "ParticleGraphicsComponent.h"
#include "../Entity.h"

ParticleGraphicsComponent::ParticleGraphicsComponent(float alphaReductionRate) : GraphicsComponent()
{
	m_alphaReductionRate = alphaReductionRate;

	//creating a simple pixel for particles
	auto shape = new sf::CircleShape(5.0f, 4);
	shape->setOrigin(0.5f, 0.5f);
	shape->setFillColor(sf::Color(255,255,255,0));

	m_shape = shape;
}


ParticleGraphicsComponent::~ParticleGraphicsComponent()
{
}

void ParticleGraphicsComponent::Update(const Entity& entity, sf::RenderWindow& window, float dtTimeMilli)
{
	//simple particle, so only update position, NOT rotation
	if (m_shape) {

		int alpha = m_shape->getFillColor().a;
		if (alpha > 0) {
			m_shape->setPosition(entity.GetPosition());
			window.draw(*m_shape);
			alpha -= dtTimeMilli * m_alphaReductionRate;
			UpdateColorAlpha(alpha);
		}
	}
}

void ParticleGraphicsComponent::Enable()
{
	UpdateColorAlpha(255);
}

void ParticleGraphicsComponent::UpdateColorAlpha(int newAlpha)
{
	if (newAlpha > 255)
		newAlpha = 255;
	else if (newAlpha < 0)
		newAlpha = 0;

	auto color = m_shape->getFillColor();

	//todo this may slow things down alot since I'm creating a color object here?
	m_shape->setFillColor(sf::Color(color.r, color.g, color.b, newAlpha));
}
