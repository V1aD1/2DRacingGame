#include "EntityFactory.h"
#include "Entity.h"

#include "Particle/ParticleGraphicsComponent.h"

#include "Car/CarPhysicsComponent.h"
#include "Particle/ParticlePhysicsComponent.h"
#include "Terrain/TerrainPhysicsComponent.h"

#include "Car/InputComponentP1.h"
#include "Car/InputComponentP2.h"

#include "../Components/StaticCollisionComponent.h"
#include "../Components/VariableCollisionComponent.h"
#include "../Components/ShapeGraphicsComponent.h"
#include "../Components/SpriteGraphicsComponent.h"

#include "../Other/MathCommon.h"

const float EntityFactory::c_car_length = 40.0f;
const float EntityFactory::c_car_width = 10.0f;


Entity* EntityFactory::DBG_CreateSquare(float sideLen, sf::Vector2f startPos, float startRotInDeg) {
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color::Red);

	std::vector<sf::Vector2f> localCorners;

	localCorners.push_back(sf::Vector2f(-halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, halfSideLen));
	localCorners.push_back(sf::Vector2f(-halfSideLen, halfSideLen));

	auto graphics = new ShapeGraphicsComponent(shape);
	auto collision = new StaticCollisionComponent(startPos, MathCommon::DegreesToRadians(startRotInDeg), localCorners);

	return new Entity(startPos, startRotInDeg, nullptr, nullptr, graphics, collision);
}

Entity* EntityFactory::CreateStaticCollisionObject(sf::Vector2f startPos, float startRotInDeg, sf::Vector2f scale, sf::Texture& text)
{
	auto size = text.getSize();

	//create shape for graphics component
	sf::Sprite* sprite = new sf::Sprite(text);
	//origin must ignore all transformation applied to the texture!!
	sprite->setOrigin(size.x / 2.0f, size.y / 2.0f);

	sprite->setScale(scale);

	//create corners for physics component
	std::vector<sf::Vector2f> localCorners = std::vector<sf::Vector2f>();
	localCorners.push_back(sf::Vector2f(-(size.x * scale.x / 2.0f), -(size.y * scale.y / 2.0f)));
	localCorners.push_back(sf::Vector2f(size.x * scale.x / 2.0f, -(size.y * scale.y / 2.0f)));
	localCorners.push_back(sf::Vector2f(size.x * scale.x / 2.0f, size.y * scale.y / 2.0f));
	localCorners.push_back(sf::Vector2f(-(size.x * scale.x / 2.0f), size.y * scale.y / 2.0f));

	//todo use TextureGraphicsComponent or something
	auto graphics = new SpriteGraphicsComponent(sprite);
	auto collision = new StaticCollisionComponent(startPos, MathCommon::DegreesToRadians(startRotInDeg), localCorners);

	return new Entity(startPos, startRotInDeg, nullptr, nullptr, graphics, collision);
}

//todo variable objects are drawn above decorative ones, fix that
Entity * EntityFactory::CreateDecorativeObject(sf::Vector2f startPos, float startRotInDeg, sf::Vector2f scale, sf::Texture& text)
{
	auto size = text.getSize();

	//create shape for graphics component
	sf::Sprite* sprite = new sf::Sprite(text);
	//origin must ignore all transformation applied to the texture!!
	sprite->setOrigin(size.x / 2.0f, size.y / 2.0f);

	sprite->setScale(scale);

	//create corners for physics component
	std::vector<sf::Vector2f> localCorners = std::vector<sf::Vector2f>();
	localCorners.push_back(sf::Vector2f(-(size.x * scale.x / 2.0f), -(size.y * scale.y / 2.0f)));
	localCorners.push_back(sf::Vector2f(size.x * scale.x / 2.0f, -(size.y * scale.y / 2.0f)));
	localCorners.push_back(sf::Vector2f(size.x * scale.x / 2.0f, size.y * scale.y / 2.0f));
	localCorners.push_back(sf::Vector2f(-(size.x * scale.x / 2.0f), size.y * scale.y / 2.0f));

	//todo use TextureGraphicsComponent or something
	auto graphics = new SpriteGraphicsComponent(sprite);

	return new Entity(startPos, startRotInDeg, nullptr, nullptr, graphics, nullptr);
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
	auto graphics = new SpriteGraphicsComponent(sprite);
	auto collision = new VariableCollisionComponent(startPos, 0.0f, corners);

	return new Entity(startPos, startRotInDeg, inputCom, physics, graphics, collision);
}

Entity * EntityFactory::CreateParticle(float alphaChangeRate)
{
	return new Entity(sf::Vector2f(50, 500), 0, nullptr, new ParticlePhysicsComponent(), new ParticleGraphicsComponent(alphaChangeRate), nullptr);
}

Entity * EntityFactory::CreateGrassTerrain(float sideLen, sf::Vector2f startPos, sf::Vector2f scale)
{
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color(86, 176, 0));

	std::vector<sf::Vector2f> localCorners;

	localCorners.push_back(sf::Vector2f(-halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, halfSideLen));
	localCorners.push_back(sf::Vector2f(-halfSideLen, halfSideLen));

	//default physics component is non-kinematic by default
	auto physics = new TerrainPhysicsComponent(startPos, localCorners, CarPhysicsComponent::car_frictionForce + 0.1f, CarPhysicsComponent::car_maxSpeed / 2);
	auto graphics = new ShapeGraphicsComponent(shape);
	auto collision = new StaticCollisionComponent(startPos, MathCommon::DegreesToRadians(0), localCorners);

	return new Entity(startPos, 0, nullptr, physics, graphics, collision);
}

Entity * EntityFactory::CreateDirtTerrain(float sideLen, sf::Vector2f startPos, sf::Vector2f scale)
{
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color(160, 82, 45));

	std::vector<sf::Vector2f> localCorners;

	localCorners.push_back(sf::Vector2f(-halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, halfSideLen));
	localCorners.push_back(sf::Vector2f(-halfSideLen, halfSideLen));

	//default physics component is non-kinematic by default
	auto physics = new TerrainPhysicsComponent(startPos, localCorners, CarPhysicsComponent::car_frictionForce, CarPhysicsComponent::car_maxSpeed * 0.7);
	auto graphics = new ShapeGraphicsComponent(shape);
	auto collision = new StaticCollisionComponent(startPos, MathCommon::DegreesToRadians(0), localCorners);

	return new Entity(startPos, 0, nullptr, physics, graphics, collision);
}

Entity * EntityFactory::CreateRoadTerrain(float sideLen, sf::Vector2f startPos, sf::Vector2f scale)
{
	float halfSideLen = sideLen / 2;

	sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape->setOrigin(halfSideLen, halfSideLen);
	shape->setFillColor(sf::Color(128, 128, 128));

	std::vector<sf::Vector2f> localCorners;

	localCorners.push_back(sf::Vector2f(-halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, -halfSideLen));
	localCorners.push_back(sf::Vector2f(halfSideLen, halfSideLen));
	localCorners.push_back(sf::Vector2f(-halfSideLen, halfSideLen));

	//default physics component is non-kinematic by default
	auto physics = new TerrainPhysicsComponent(startPos, localCorners, CarPhysicsComponent::car_frictionForce, CarPhysicsComponent::car_maxSpeed);
	auto graphics = new ShapeGraphicsComponent(shape);
	auto collision = new StaticCollisionComponent(startPos, MathCommon::DegreesToRadians(0), localCorners);

	return new Entity(startPos, 0, nullptr, physics, graphics, collision);
}





