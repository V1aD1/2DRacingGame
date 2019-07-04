#include "EntityFactory.h"
#include "Entity.h"

#include "Static/SquareGraphicsComponent.h"
#include "Car/CarGraphicsComponent.h"
#include "Car/CarGraphicsComponentV2.h"
#include "Particle/ParticleGraphicsComponent.h"

#include "Car/CarPhysicsComponent.h"
#include "Particle/ParticlePhysicsComponent.h"

#include "Car/InputComponentP1.h"
#include "Car/InputComponentP2.h"

#include "../Components/StaticCollisionComponent.h"
#include "../Components/VariableCollisionComponent.h"

#include "../Other/MathCommon.h"

const float EntityFactory::c_car_length = 40.0f;
const float EntityFactory::c_car_width = 10.0f;


Entity* EntityFactory::CreateSquare(float sideLen, sf::Vector2f pos, float rotDeg) {
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color::Red);

	std::vector<sf::Vector2f> localCorners;
	std::vector<sf::Vector2f> worldCorners;


	localCorners.push_back(sf::Vector2f(-halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, halfSideLen));
	localCorners.push_back(sf::Vector2f(-halfSideLen, halfSideLen));

	auto graphics = new SquareGraphicsComponent(shape);
	auto collision = new StaticCollisionComponent(pos, MathCommon::DegreesToRadians(rotDeg), localCorners);

	return new Entity(pos, rotDeg, nullptr, nullptr, graphics, collision);
}

Entity* EntityFactory::CreatePlayer1(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText)
{
	return CreateCar(startPos, startRotInDeg, carText, new InputComponentP1());
}

Entity* EntityFactory::CreatePlayer2(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText)
{
	return CreateCar(startPos, startRotInDeg, carText, new InputComponentP2());
}

Entity* EntityFactory::CreateCar(sf::Vector2f startPos, float startRotInDeg, sf::Texture& carText, InputComponent* inputCom)
{
	auto size = carText.getSize();

	//create shape for graphics component
	sf::Sprite* sprite = new sf::Sprite(carText);
	//origin must ignore all transformation applied to the texture!!
	sprite->setOrigin(size.x / 2.0f, size.y / 2.0f);

	//resizing texture, only comparing length
	auto scale = sf::Vector2f(c_car_length / size.y, c_car_length / size.y);
	sprite->setScale(scale);

	//create corners for physics component
	std::vector<sf::Vector2f> corners = std::vector<sf::Vector2f>();
	corners.push_back(sf::Vector2f(-(size.x * scale.x / 2.0f), -(size.y * scale.y / 2.0f)));
	corners.push_back(sf::Vector2f(size.x * scale.x / 2.0f, -(size.y * scale.y / 2.0f)));
	corners.push_back(sf::Vector2f(size.x * scale.x / 2.0f, size.y * scale.y / 2.0f));
	corners.push_back(sf::Vector2f(-(size.x * scale.x / 2.0f), size.y * scale.y / 2.0f));

	auto physics = new CarPhysicsComponent(startPos, 0.0f, corners);
	auto graphics = new CarGraphicsComponentV2(sprite);
	auto collision = new VariableCollisionComponent(startPos, 0.0f, corners);

	return new Entity(startPos, startRotInDeg, inputCom, physics, graphics, collision);
}

Entity * EntityFactory::CreateParticle(float alphaChangeRate)
{
	return new Entity(sf::Vector2f(50, 500), 0, nullptr, new ParticlePhysicsComponent(), new ParticleGraphicsComponent(alphaChangeRate), nullptr);
}





