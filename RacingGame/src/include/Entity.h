#include <array>
#include <SFML/Graphics.hpp>

#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"

#include "EventHandler.h"

class EventHandler;

#pragma once
class Entity
{

private:
	float m_rotation;
	float m_rotationInRad;

protected:
	sf::Vector2f m_position;

public: 
	InputComponent* m_input;
	PhysicsComponent* m_physics;
	GraphicsComponent* m_graphics;
	CollisionComponent* m_collision;

public:
	Entity();
	Entity(sf::Vector2f position, float rotDeg);
	Entity(sf::Vector2f position, float rotDeg, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics, CollisionComponent* collision);
	~Entity();

	void Update(sf::RenderWindow& window, float dtTimeMilli, const EventHandler& handler);

	sf::Vector2f GetPosition() const;
	float GetRotationInDegrees() const;
	float GetRotationInRadians() const;

	//todo shouldn't be 4 corners
	virtual const std::array<sf::Vector2f, 4>* GetWorldCorners() const;
	
	void SetRotation(float degrees);
	void SetPosition(sf::Vector2f newPos);

	void Rotate(float degrees);

};

