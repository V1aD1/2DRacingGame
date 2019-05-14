#pragma once

#include <SFML/Graphics.hpp>

class ParticleEmitter
{
private:
	static const int c_pool_size = 1000;

public:
	static void Init();
	static void EmitCircle(sf::Vector2f pos, float speed, float alphaChangeRate, int numParticles);
	static void EmitCone(sf::Vector2f pos, sf::Vector2f dir, float speed, float acc, float alphaChangeRate, float scaleRateChange, int coneWidth, int numParticles);
};