#include "include/ParticleEmitter.h"
#include "include/EntityFactory.h"

std::vector<Entity*> G_PARTICLES;

ParticleEmitter::ParticleEmitter()
{
	for (int i = 0; i < c_pool_size; i++) {
		G_PARTICLES.push_back(EntityFactory::CreateParticle());
	}
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::EmitCircle(sf::Vector2f pos, int numParticles)
{
}

void ParticleEmitter::EmitCone(sf::Vector2f pos, sf::Vector2f dir, int numParticles)
{
}
