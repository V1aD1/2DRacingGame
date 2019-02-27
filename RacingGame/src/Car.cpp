#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "include/Car.h"
#include "include/Entity.h"
#include "include/InputComponent.h"
#include "include/CarPhysicsComponent.h"
#include "include/CarGraphicsComponent.h"

const float Car::c_length = 40.0f;
const float Car::c_height = 10.0f;

Car::Car(sf::Vector2f startPos): Entity(startPos, 0.0f){
	auto size = sf::Vector2f(c_length, c_height);

	//create shape for graphics component
	sf::RectangleShape* shape = new sf::RectangleShape(size);
	shape->setFillColor(sf::Color::Blue);
	shape->setOutlineThickness(1.0f);
	shape->setOutlineColor(sf::Color(250, 150, 100));
	shape->setOrigin(size.x / 2.0f, size.y / 2.0f);
	shape->setPosition(0.0f, 0.0f);


	//create corners for physics component
	std::array<sf::Vector2f, 4> corners = std::array<sf::Vector2f, 4>();
	corners[0] = sf::Vector2f(-size.x / 2.0f, -size.y / 2.0f);
	corners[1] = sf::Vector2f(size.x / 2.0f, -size.y / 2.0f);
	corners[2] = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
	corners[3] = sf::Vector2f(-size.x / 2.0f, size.y / 2.0f);

	m_input = new InputComponent();
	m_physics = new CarPhysicsComponent(this, corners);
	m_graphics = new CarGraphicsComponent(shape);
	m_collision = new CollisionComponent(startPos, 0.0f, corners);
}

Car::~Car() {
	
}