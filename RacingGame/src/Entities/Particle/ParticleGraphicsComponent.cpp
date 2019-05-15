#include "ParticleGraphicsComponent.h"
#include "../Entity.h"

ParticleGraphicsComponent::ParticleGraphicsComponent(float alphaChangeRate) : GraphicsComponent()
{
	auto radius = 5.0f;
	m_alphaChangeRate = alphaChangeRate;

	//creating a simple pixel for particles
	auto shape = new sf::CircleShape(radius, 4);
	shape->setOrigin(radius, radius);
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
			alpha += dtTimeMilli/1000.0f * m_alphaChangeRate;
			UpdateColorAlpha(alpha);
		}

		auto scale = m_shape->getScale();
		if (scale.x > 0.0f || scale.y > 0.0f) {
			m_shape->setScale(scale.x + m_scaleChangeRate * dtTimeMilli / 1000.0f, scale.y + m_scaleChangeRate * dtTimeMilli / 1000.0f);
		}
	}
}

void ParticleGraphicsComponent::Enable()
{
	UpdateColorAlpha(255);
	m_shape->setScale(1, 1);
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
