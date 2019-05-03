#include <stdlib.h>

#include "include/ParticleEmitter.h"
#include "include/EntityFactory.h"
#include "include/MathCommon.h"
#include "include/ParticleGraphicsComponent.h"

std::vector<Entity*> G_PARTICLES;

void ParticleEmitter::Init()
{
	for (int i = 0; i < c_pool_size; i++) {
		G_PARTICLES.push_back(EntityFactory::CreateParticle(0.2f));
	}
}

void ParticleEmitter::EmitCircle(sf::Vector2f pos, int numParticles)
{
	for (auto particle : G_PARTICLES) {
		if (numParticles == 0)
			break;

		auto shape = particle->m_graphics->GetShape();

		if (shape->getFillColor().a == 0) {
			particle->SetPosition(pos);
			particle->SetRotation(rand() % 361);
			particle->m_physics->SetSpeed(0.3f);
			particle->m_graphics->Enable();

			numParticles--;
		}
	}
}

void ParticleEmitter::EmitCone(sf::Vector2f pos, sf::Vector2f dir, int coneWidth, int numParticles)
{
	float angleBetweenVecs = MathCommon::GetAngleBetweenVectorsInRads(dir, sf::Vector2f(1, 0));
	if (dir.y < 0) { angleBetweenVecs = -angleBetweenVecs; }

	if (coneWidth < 2) { coneWidth = 2; }

	float angleInDegrees = MathCommon::RadiansToDegrees(angleBetweenVecs);

	for (auto particle : G_PARTICLES) {
		if (numParticles == 0)
			break;

		auto shape = particle->m_graphics->GetShape();

		//todo remove the code repetition between the Emit...() functions
		if (shape->getFillColor().a == 0) {
			particle->SetPosition(pos);
			particle->SetRotation(rand() % (coneWidth)-(coneWidth / 2) + angleInDegrees);
			particle->m_physics->SetSpeed(0.3f);
			particle->m_graphics->Enable();

			numParticles--;
		}
	}
}
