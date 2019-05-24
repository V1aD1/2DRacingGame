#include "ParticleEmitter.h"
#include "../EntityFactory.h"
#include "../../Other/MathCommon.h"
#include "ParticleGraphicsComponent.h"
#include "../Entity.h"

std::vector<Entity*> G_PARTICLES;

void ParticleEmitter::Init()
{
	for (int i = 0; i < c_pool_size; i++) {
		G_PARTICLES.push_back(EntityFactory::CreateParticle(0.2f));
	}
}

void ParticleEmitter::EmitCircle(sf::Vector2f pos, float startSpeed, float maxSpeed, float acc, float alphaChangeRate, float scaleRateChange, int numParticles, int randRotRange)
{
	for (auto particle : G_PARTICLES) {
		if (numParticles == 0)
			break;

		auto shape = particle->m_graphics->GetShape();

		if (shape->getFillColor().a == 0) {
			SetParticleAttributesExceptRotation(particle, std::rand() % 361, pos, startSpeed, maxSpeed, acc, alphaChangeRate, scaleRateChange, randRotRange);
			particle->m_graphics->Enable();

			numParticles--;
		}
	}
}

///Note, for alphaReductionRate, short life = 1, long life = 0.1
void ParticleEmitter::EmitCone(
	sf::Vector2f pos, 
	sf::Vector2f dir, 
	float startSpeed, 
	float maxSpeed, 
	float acc, 
	float alphaChangeRate, 
	float scaleRateChange, 
	int coneWidth, 
	int numParticles, 
	int randRotRange)
{
	float angleBetweenVecs = MathCommon::GetAngleBetweenVectorsInRads(dir, sf::Vector2f(1, 0));
	if (dir.y < 0) { angleBetweenVecs = -angleBetweenVecs; }

	if (coneWidth < 2) { coneWidth = 2; }

	float angleInDegrees = MathCommon::RadiansToDegrees(angleBetweenVecs);

	for (auto particle : G_PARTICLES) {
		if (numParticles == 0)
			break;

		auto shape = particle->m_graphics->GetShape();

		//todo add two lists for the particles, one for free particles, another for in use particles
		//	probably graphics component would have to add the particles to the free list once their
		//	alpha reaches 0
		if (shape->getFillColor().a == 0) {
			SetParticleAttributesExceptRotation(particle, std::rand() % (coneWidth)-(coneWidth / 2) + angleInDegrees, pos, startSpeed, maxSpeed, acc, alphaChangeRate, scaleRateChange, randRotRange);
			particle->m_graphics->Enable();

			numParticles--;
		}
	}
}

void ParticleEmitter::SetParticleAttributesExceptRotation(
	Entity* particle, 
	float rotDegrees, 
	sf::Vector2f pos, 
	float startSpeed, 
	float maxSpeed, 
	float acc, 
	float alphaChangeRate, 
	float scaleRateChange, 
	int randRotRange)
{
	//rotation must be set before speed!
	particle->SetRotation(rotDegrees);
	particle->SetPosition(pos);
	particle->m_physics->SetSpeed(startSpeed);
	particle->m_physics->SetMaxSpeed(maxSpeed);
	particle->m_physics->SetAcceleration(acc);
	particle->m_physics->SetRandomness(randRotRange);
	particle->m_graphics->SetAlphaChangeRate(alphaChangeRate);
	particle->m_graphics->SetScaleChangeRate(scaleRateChange);
}
