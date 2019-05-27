#pragma once

#include <array>
#include <SFML/Graphics.hpp>

class Entity;
class CollisionComponent;

class PhysicsState
{
private:

	sf::Vector2f m_worldPos = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f m_velocity;
	
	float m_currentAcceleration;
	float m_rotInRad = 0.0f;

	CollisionComponent* m_collisionComp;
	std::vector<sf::Vector2i> m_collisionSpaceCoords;

public:
	PhysicsState(sf::Vector2f pos, float rotRad, const std::vector<sf::Vector2f>& cornersWithoutRotationApplied);
	~PhysicsState();

public:

	void Update(float dtMilli, float maxVelocity);

	PhysicsState(const PhysicsState& other);
	PhysicsState& operator=(const PhysicsState& other);

	void Rotate(float radsToTurn);
	void SetRotation(float newRotInRad);
	void SetCurrentAcceleration(float newAcc);

	void ApplyVelocity(sf::Vector2f force);

	const std::vector<sf::Vector2f>& GetWorldCorners() const;
	const std::vector<sf::Vector2i>& GetCollisionSpaceCoordinates() const;
	sf::Vector2f GetWorldPosition() const;
	sf::Vector2f GetVelocity() const;
	sf::Vector2f GetForwardDir() const;
	float GetRotInRad() const;
	float GetCurrentAcceleration() const;

	//should ONLY be used by DBG_ commands
	void SetWorldPos(sf::Vector2f newPos);
	void SetVelocity(sf::Vector2f newVelocity);

	std::tuple<bool, sf::Vector2f> IsColliding(const std::vector<sf::Vector2f>* otherEntityWorldCornersPtr) const;

private:
	void UpdateToNewState(const PhysicsState& other);
	void UpdateForwardDir();
};

