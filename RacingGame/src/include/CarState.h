#pragma once
#include <array>
#include <SFML/Graphics.hpp>

class Entity;

class CarState{
private:
	static const float c_maxMomentum;

private:
	sf::Vector2f m_worldPos = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f m_forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f m_momentum = sf::Vector2f(0.0f, 0.0f);
	std::array<sf::Vector2f, 4> m_localCorners;
	std::array<sf::Vector2f, 4> m_worldCorners;

public:
	float m_rotInRad = 0.0f;

public:
	CarState(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	~CarState();

	void Update(float dtMilli);
	
	CarState& operator=(const CarState& other);

	void Rotate(float radsToTurn);
	void Accelerate(float acceleration);
	void ApplyForce(sf::Vector2f force);

	const std::array<sf::Vector2f, 4>* GetWorldCorners() const;
	sf::Vector2f GetWorldPosition();
	sf::Vector2f GetMomentum();

	//should ONLY be used by DBG_ commands
	void SetWorldPos(sf::Vector2f newPos);
	void SetMomentum(sf::Vector2f newMomentum);
};

