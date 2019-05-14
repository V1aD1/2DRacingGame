#pragma once

#include "../../Components/GraphicsComponent.h"

class ParticleGraphicsComponent : public GraphicsComponent
{
public:
	ParticleGraphicsComponent(float alphaChangeRate);
	~ParticleGraphicsComponent();

public:
	void Update(const Entity& entity, sf::RenderWindow & window, float dtTimeMilli) override;
	void Enable() override;

private:
	void UpdateColorAlpha(int newAlpha);
};

