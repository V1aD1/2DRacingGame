#pragma once

#include "GraphicsComponent.h"

class ParticleGraphicsComponent : public GraphicsComponent
{
private:
	float m_alphaReductionRate = 0;


public:
	ParticleGraphicsComponent(float alphaReductionRate);
	~ParticleGraphicsComponent();

public:
	void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
	void HandleCollision(sf::Vector2f otherEntityMomentum) override;
	void Enable() override;

private:
	void UpdateColorAlpha(int newAlpha);
};

