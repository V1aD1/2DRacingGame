#pragma once
#include "../../Components/PhysicsComponentV2.h"

class Entity;

class ParticlePhysicsComponent : public PhysicsComponentV2
{
public:
	ParticlePhysicsComponent();
	~ParticlePhysicsComponent();

	void Update(Entity& entity, float dtMilli) override;
	sf::Vector2f HandleCollision(sf::Vector2f otherEntityVel) override;
	void DBG_Slide(Entity& entity, const sf::Vector2f& dir, float dtMilli) override;
	
	//todo particles don't need a "brake" function
	void Brake(float dtTimeMilli) override;

private:

	//todo yeah this shouldn't be necessary, gotta fixup physics system...
	float particle_maxSpeed = 1.0f;
};

