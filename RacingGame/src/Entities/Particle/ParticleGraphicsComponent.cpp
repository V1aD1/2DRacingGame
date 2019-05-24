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

		int alpha = m_shape->getFillColor().a;
		if (alpha > 0) {
			m_shape->setPosition(entity.GetPosition());
			window.draw(*m_shape);
			alpha += dtTimeMilli/1000.0f * m_alphaChangeRate;
			UpdateColorAlpha(alpha);

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
	color.a = newAlpha;
	m_shape->setFillColor(color);
}
