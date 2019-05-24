#pragma once
#include "../../Components/PhysicsComponent.h"

class Entity;

class ParticlePhysicsComponent : public PhysicsComponent
{
public:
	ParticlePhysicsComponent();
	~ParticlePhysicsComponent();

	void Update(Entity& entity, float dtMilli) override;
	void SetRandomness(int newRand) override;

private:
	int m_randRotRange;
};

