#pragma once
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "ConvexEntity.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "VariableEntity.h"
#include "CarState.h"

extern std::vector<ConvexEntity*> G_STATICOBJECTS;

class Car : public VariableEntity
{
public:
	static const float c_length;
	static const float c_height;
	static const float c_rotationSpeed;
	static const float c_acceleration;
	static const float c_brakeForce;
	static const float c_frictionForce;
	static const float c_dbg_slideSpeed;
	static const float c_maxMomentum;

private:
	CarState newState;
	CarState currState;
	InputComponent* input;
	PhysicsComponent* physics;

public:
	Car(sf::Vector2f pos);
	
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(const sf::Vector2f& dir, float dtMilli);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);
	void ApplyFriction(float dtTimeMilli);
	bool CollisionDetected();	
	virtual void Update(sf::RenderWindow& window,float dtTimeMilli, EventHandler& handler);

	~Car();

};

