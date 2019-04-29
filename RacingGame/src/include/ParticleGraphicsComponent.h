#pragma once

#include "GraphicsComponent.h"

class ParticleGraphicsComponent : public GraphicsComponent
{
public:
	ParticleGraphicsComponent();
	~ParticleGraphicsComponent();

public:
	virtual void Update(const Entity& entity, sf::RenderWindow & window) override;
	virtual void HandleCollision(sf::Vector2f otherEntityMomentum) override;
};

