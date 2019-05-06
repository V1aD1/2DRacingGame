#pragma once

#include "../../Components/GraphicsComponent.h"

class ParticleGraphicsComponent : public GraphicsComponent
{
private:
	float m_alphaReductionRate = 0;


public:
	ParticleGraphicsComponent(float alphaReductionRate);
	~ParticleGraphicsComponent();

public:
	void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
	void Enable() override;

private:
	void UpdateColorAlpha(int newAlpha);
};

