#include <stdlib.h>

#include "include/ParticleEmitter.h"
#include "include/EntityFactory.h"
#include "include/MathCommon.h"

std::vector<Entity*> G_PARTICLES;

ParticleEmitter::ParticleEmitter()
{
	for (int i = 0; i < c_pool_size; i++) {
		G_PARTICLES.push_back(EntityFactory::CreateParticle(0.2f));
	}
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::EmitCircle(sf::Vector2f pos, int numParticles)
{
	int count = 0;
	for (auto particle : G_PARTICLES) {

		auto shape = particle->m_graphics->GetShape();
			
		if (shape->getFillColor().a == 0) {
			particle->SetPosition(pos);
			particle->SetRotation(rand() % 361);
			particle->m_physics->SetSpeed(0.3f);
			particle->m_graphics->Enable();

			count++;

			if (count >= numParticles)
				break;
		}
	}
}

void ParticleEmitter::EmitCone(sf::Vector2f pos, sf::Vector2f dir, int numParticles)
{
	float angleInDegrees = MathCommon::RadiansToDegrees(MathCommon::GetAngleBetweenVectorsInRads(dir, sf::Vector2f(1, 0)));

	int count = 0;
	for (auto particle : G_PARTICLES) {

		auto shape = particle->m_graphics->GetShape();


		//todo remove the code repetition between the Emit...() functions
		if (shape->getFillColor().a == 0) {
			particle->SetPosition(pos);
			particle->SetRotation(rand() % 10 + angleInDegrees);
			particle->m_physics->SetSpeed(0.3f);
			particle->m_graphics->Enable();

			count++;

			if (count >= numParticles)
				break;
		}
	}
}
