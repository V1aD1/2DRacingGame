#pragma once
#include <array>
#include <SFML/Graphics.hpp>

class Entity;

class CarState{

public:
	sf::Vector2f worldPos = sf::Vector2f(0.0f, 0.0f);
	float rotInRad = 0.0f;
	sf::Vector2f forwardDir = sf::Vector2f(1.0f, 0.0f);
	sf::Vector2f momentum = sf::Vector2f(0.0f, 0.0f);
	std::array<sf::Vector2f, 4> m_localCorners;
	std::array<sf::Vector2f, 4> m_worldCorners;

public:
	CarState(Entity* entity, const std::array<sf::Vector2f, 4>& cornersWithoutRotationApplied);
	~CarState();

	void UpdateToNewState(const CarState& newState);
	void Rotate(float radsToTurn, sf::Vector2f entityWorldPos);
};

