#include <array>
#include <SFML/Graphics.hpp>

#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

#include "EventHandler.h"

#pragma once
class Entity
{

//todo make private since rotation should only be changeable through SetRotation()
protected:
	sf::Vector2f m_position;
	float m_rotation;
	float m_rotationInRad;

public:
	Entity(sf::Vector2f position, float rot, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	~Entity();

	void Update(sf::RenderWindow& window, float dtTimeMilli, const EventHandler& handler);

	sf::Vector2f GetPosition() const;
	float GetRotationInDegrees() const;
	float GetRotationInRadians() const;

	//sets both the m_rotation and m_rotationInRad
	void SetRotation(float degrees);
	void SetPosition(sf::Vector2f newPos);

private:
	InputComponent* m_input;
	PhysicsComponent* m_physics;
	GraphicsComponent* m_graphics;
};

