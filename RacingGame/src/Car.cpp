#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "include/Car.h"
#include "include/MathCommon.h"
#include "include/Square.h"
#include "include/EventHandler.h"

const float Car::c_length = 40.0f;
const float Car::c_height = 10.0f;

const float Car::c_rotationSpeed = 180.0f;
const float Car::c_acceleration = 0.25f;
const float Car::c_brakeForce = 0.1f;
const float Car::c_frictionForce = 0.1f;
const float Car::c_dbg_slideSpeed = 150.0f;
const float Car::c_maxMomentum = 0.3f;

Car::Car(sf::Vector2f startPos){

	//set rotation to 0,

	//set shape for graphics component
	sf::RectangleShape* shape = new sf::RectangleShape(size);
	shape->setFillColor(sf::Color::Blue);
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(sf::Color(250, 150, 100));
	shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
	shape->setPosition(0.0f, 0.0f);
	SetShape(shape);

	//set corners for physics component
	std::array<sf::Vector2f, 4> corners = std::array<sf::Vector2f, 4>();
	corners[0] = sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f);
	corners[1] = sf::Vector2f(size.x / 2.0f, -size.y / 2.0f);
	corners[2] = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
	corners[3] = sf::Vector2f(-size.x / 2.0f, size.y / 2.0f);
	SetCorners(corners);

}

Car::~Car() {

	//delete graphics component m_shape here
}