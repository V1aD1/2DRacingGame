#include "include/Entity.h"
#include "include/GraphicsComponent.h"


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

