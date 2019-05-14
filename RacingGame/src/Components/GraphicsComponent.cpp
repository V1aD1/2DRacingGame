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

GraphicsComponent::~GraphicsComponent()
{
	delete m_shape;
}

sf::Shape* GraphicsComponent::GetShape()
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

