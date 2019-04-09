#pragma once
#include <array>
#include <SFML/Graphics.hpp>


class Entity;
class CollisionComponent;

class PhysicsState {
private:
	sf::Vector2f m_worldPos = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f m_momentum = sf::Vector2f(0.0f, 0.0f);
	CollisionComponent* m_collisionComp;
	float m_rotInRad = 0.0f;
	std::vector<sf::Vector2i> m_collisionSpaceCoords;

public:
	PhysicsState(sf::Vector2f pos, float rotRad, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	~PhysicsState();

	void Update(float dtMilli, float maxMomentum);

	PhysicsState(const PhysicsState& other);
	PhysicsState& operator=(const PhysicsState& other);

	void Rotate(float radsToTurn);
	void Accelerate(float acceleration);
	void ApplyForce(sf::Vector2f force);

public:
	const std::array<sf::Vector2f, 4>& GetWorldCorners() const;
	const std::vector<sf::Vector2i>& GetCollisionSpaceCoordinates() const;
	sf::Vector2f GetWorldPosition();
	sf::Vector2f GetMomentum();
	float GetRotInRad();

	//should ONLY be used by DBG_ commands
	void SetWorldPos(sf::Vector2f newPos);
	void SetMomentum(sf::Vector2f newMomentum);

private:
	void UpdateToNewState(const PhysicsState& other);
};

