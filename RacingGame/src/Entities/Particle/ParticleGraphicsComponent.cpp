#include <stack>

#include "ParticleGraphicsComponent.h"
#include "../Entity.h"


extern std::stack<Entity*> G_FREEPARTICLES;

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

void ParticleGraphicsComponent::Update(Entity& entity, sf::RenderWindow& window, float dtTimeMilli)
{
	//simple particle, so only update position, NOT rotation
	if (m_shape) {

		if (m_shape->getFillColor().a > 0) {
			m_shape->setPosition(entity.GetPosition());
			window.draw(*m_shape);
			m_currAlpha += dtTimeMilli/1000.0f * m_alphaChangeRate;
			UpdateColorAlphaToCurrAlpha();

			if (m_shape->getFillColor().a == 0) {
				G_FREEPARTICLES.push(&entity);
			}
		}

		auto scale = m_shape->getScale();
		if (scale.x > 0.0f || scale.y > 0.0f) {
			m_shape->setScale(scale.x + m_scaleChangeRate * dtTimeMilli / 1000.0f, scale.y + m_scaleChangeRate * dtTimeMilli / 1000.0f);
		}
	}
}

void ParticleGraphicsComponent::Enable()
{
	m_currAlpha = 255;
	UpdateColorAlphaToCurrAlpha();
	m_shape->setScale(1, 1);
}

void ParticleGraphicsComponent::UpdateColorAlphaToCurrAlpha()
{
	if (m_currAlpha > 255)
		m_currAlpha = 255;
	else if (m_currAlpha < 0)
		m_currAlpha = 0;
	

	auto color = m_shape->getFillColor();
	color.a = m_currAlpha;
	m_shape->setFillColor(color);
}
