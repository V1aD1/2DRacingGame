#pragma once

#include <SFML/Graphics.hpp>

class Entity;

class ParticleEmitter
{
private:
	static const int c_pool_size = 1000;

public:
	static void Init();
	static void EmitCircle(sf::Vector2f pos, float startSpeed, float maxSpeed, float acc, float alphaChangeRate, float scaleRateChange, int numParticles);
	static void EmitCone(sf::Vector2f pos, sf::Vector2f dir, float startSpeed, float maxSpeed, float acc, float alphaChangeRate, float scaleRateChange, int coneWidth, int numParticles);

private:
	static void SetParticleAttributesExceptRotation(Entity* particle, float rotDegrees, sf::Vector2f pos, float startSpeed, float maxSpeed, float acc, float alphaChangeRate, float scaleRateChange);
};