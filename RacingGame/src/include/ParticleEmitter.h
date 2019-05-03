#pragma once

#include "Entity.h"

//todo make static?
class ParticleEmitter
{
private:
	static const int c_pool_size = 100;

public:
	static void Init();
	static void EmitCircle(sf::Vector2f pos, int numParticles);
	static void EmitCone(sf::Vector2f pos, sf::Vector2f dir, int coneWidth, int numParticles);
};