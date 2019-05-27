#pragma once

#include "../../Components/GraphicsComponent.h"

class ParticleGraphicsComponent : public GraphicsComponent
{
public:
	ParticleGraphicsComponent(float alphaChangeRate);
	~ParticleGraphicsComponent();

public:
	void Update(Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
	void Enable() override;

private:
	void UpdateColorAlphaToCurrAlpha();

private:
	float m_currAlpha = 0;
};

