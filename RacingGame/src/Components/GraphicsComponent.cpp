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

void GraphicsComponent::SetAlphaReductionRate(float newAlphaReductionRate)
{
	m_alphaReductionRate = newAlphaReductionRate;
}

