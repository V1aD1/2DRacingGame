#include <stack>

#include "ParticleEmitter.h"
#include "../EntityFactory.h"
#include "../../Other/MathCommon.h"
#include "ParticleGraphicsComponent.h"
#include "../Entity.h"

std::vector<Entity*> G_PARTICLES;
std::stack<Entity*> G_FREEPARTICLES;

void ParticleEmitter::Init()
{
	G_PARTICLES.reserve(c_pool_size);

	for (int i = 0; i < c_pool_size; i++) {
		auto newParticle = EntityFactory::CreateParticle(0.2f);
		G_PARTICLES.push_back(newParticle);
		G_FREEPARTICLES.push(newParticle);
	}
}

void ParticleEmitter::EmitCircle(sf::Vector2f pos, float startSpeed, float maxSpeed, float acc, float timeToLiveInSeconds, float scaleRateChange, int numParticles, int randRotRange)
{
	float alphaChangeRate = -(255 / timeToLiveInSeconds);

	while (numParticles > 0 && !G_FREEPARTICLES.empty()) {
		auto particle = G_FREEPARTICLES.top();
		auto shape = particle->m_graphics->GetShape();

		SetParticleAttributes(particle, std::rand() % 361, pos, startSpeed, maxSpeed, acc, alphaChangeRate, scaleRateChange, randRotRange);
		particle->m_graphics->Enable();
		
		//remove in-use particle from the stack
		G_FREEPARTICLES.pop();

		numParticles--;
	}
	
}

///NOTE: for alphaReductionRate, short life = 1, long life = 0.1
void ParticleEmitter::EmitCone(
	sf::Vector2f pos,
	sf::Vector2f dir,
	float startSpeed,
	float maxSpeed,
	float acc,
	float timeToLiveInSeconds,
	float scaleRateChange,
	int coneWidth,
	int numParticles,
	int randRotRange)
{
	float angleBetweenVecs = MathCommon::GetAngleBetweenVectorsInRads(dir, sf::Vector2f(1, 0));

	if (coneWidth < 2) { coneWidth = 2; }

	float angleInDegrees = MathCommon::RadiansToDegrees(angleBetweenVecs);
	float alphaChangeRate = -(255 / timeToLiveInSeconds);
	while(numParticles > 0 && !G_FREEPARTICLES.empty()) {
		auto particle = G_FREEPARTICLES.top();
		auto shape = particle->m_graphics->GetShape();

		SetParticleAttributes(particle, std::rand() % (coneWidth)-(coneWidth / 2) + angleInDegrees, pos, startSpeed, maxSpeed, acc, alphaChangeRate, scaleRateChange, randRotRange);
		particle->m_graphics->Enable();

		//remove in-use particle from the stack
		G_FREEPARTICLES.pop();

		numParticles--;
	}
}

void ParticleEmitter::SetParticleAttributes(
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
