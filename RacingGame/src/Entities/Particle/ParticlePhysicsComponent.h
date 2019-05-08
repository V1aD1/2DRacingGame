#pragma once
#include "../../Components/PhysicsComponent.h"

class Entity;

class ParticlePhysicsComponent : public PhysicsComponent
{
public:
	ParticlePhysicsComponent();
	~ParticlePhysicsComponent();

	void Update(Entity& entity, float dtMilli) override;
	sf::Vector2f HandleCollision(sf::Vector2f otherEntityVel) override;
	void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) override;

private:

	//todo yeah this shouldn't be necessary, gotta fixup physics system...
	float particle_maxSpeed = 1.0f;
};

