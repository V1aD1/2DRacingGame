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
	//sf::Vector2f startPos, float rotRad, float speed

	int count = 0;
	float rot = 0;
	for (auto particle : G_PARTICLES) {
		particle->SetPosition(pos);
		particle->SetRotation(rot);
		particle->m_physics->SetSpeed(0.3f);
		rot += 20.0f;
		
		count++;

		if (count >= numParticles)
			break;
	}

}

void ParticleEmitter::EmitCone(sf::Vector2f pos, sf::Vector2f dir, int numParticles)
{
}
