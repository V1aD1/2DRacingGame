#include "../Entities/Entity.h"
#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
	m_shape = nullptr;
}

GraphicsComponent::GraphicsComponent(sf::Shape* shape)
{
	m_shape = shape;
}

GraphicsComponent::GraphicsComponent(sf::Sprite* sprite)
{
	m_sprite = sprite;
}

GraphicsComponent::~GraphicsComponent()
{
	if(m_shape)
		delete m_shape;
	
	if(m_sprite)
		delete m_sprite;
}

sf::Shape* GraphicsComponent::GetShape() const
{
	return m_shape;
}

void GraphicsComponent::Enable()
{
}

void GraphicsComponent::SetAlphaChangeRate(float newAlphaChangeRate)
{
	m_alphaChangeRate = newAlphaChangeRate;
}

void GraphicsComponent::SetScaleChangeRate(float newScaleChangeRate)
{
	m_scaleChangeRate = newScaleChangeRate;
}

