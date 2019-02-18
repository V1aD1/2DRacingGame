#pragma once
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "ConvexEntity.h"
#include "InputComponent.h"
#include "VariableEntity.h"

extern std::vector<ConvexEntity*> G_STATICOBJECTS;

class CarState : public ConvexEntity{
public:
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);

public:
	CarState(){}
	CarState(sf::Vector2f pos, float rot, sf::Vector2f size) : ConvexEntity(pos, rot) 
	{
		sf::RectangleShape* shape = new sf::RectangleShape(size);
		shape->setFillColor(sf::Color::Blue);
		shape->setOutlineThickness(1.0f);
		shape->setOutlineColor(sf::Color(250, 150, 100));
		shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
		shape->setPosition(0.0f, 0.0f);
		SetShape(shape);

		std::array<sf::Vector2f, 4> corners = std::array<sf::Vector2f, 4>();
		corners[0] = sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f);
		corners[1] = sf::Vector2f(size.x / 2.0f, -size.y / 2.0f);
		corners[2] = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
		corners[3] = sf::Vector2f(-size.x / 2.0f, size.y / 2.0f);
		SetCorners(corners);
	};

	void UpdateToNewState(const CarState& newState) {
		forwardDir = newState.forwardDir;
		momentum = newState.momentum;
		
		//todo extremely convoluted way to do this, should get rid of Rotate method all together
		Rotate(newState.m_rotation - m_rotation);
		SetPosition(newState.m_position);
		SetRotation(newState.m_rotation);	
	}

	~CarState() {
		delete m_shape;
	}

};

class Car : public VariableEntity
{
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

public:
	Car(sf::Vector2f pos);
	
	void Rotate(float degrees, bool left);
	void Accelerate(float dtTimeMilli, bool forward);
	void Brake(float dtTimeMilli);
	void DBG_Slide(const sf::Vector2f& dir, float dtMilli);
	virtual void Update(sf::RenderWindow& window,float dtTimeMilli, EventHandler& handler);

	~Car();

private:
	void ApplyFriction(float dtTimeMilli);
	void ApplySlowDownForce(float forceMag, float dtTimeMilli);
	bool CollisionDetected();
};

