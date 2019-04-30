#pragma once

#include "Entity.h"

//todo make static?
class ParticleEmitter
{
private:
	static const int c_pool_size = 100;

public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	void EmitCircle(sf::Vector2f pos, int numParticles);
	void EmitCone(sf::Vector2f pos, sf::Vector2f dir, int numParticles);
};