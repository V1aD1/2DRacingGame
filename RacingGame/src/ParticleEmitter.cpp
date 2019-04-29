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
