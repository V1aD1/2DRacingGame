#include "include/InputComponent.h"
#include "include/Car.h"
#include "include/PhysicsComponent.h"

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::Update(Entity& entity, PhysicsComponent* physics, const EventHandler& eventHandler, float dtMillis) {
	if (eventHandler.upFlag)
		physics->Accelerate(dtMillis, true);

	if (eventHandler.downFlag)
		physics->Accelerate(dtMillis, false);

	if (eventHandler.leftFlag) {
		//rotating entity position
		physics->Rotate(entity, dtMillis, true);
	}

	if (eventHandler.rightFlag) {
		physics->Rotate(entity, dtMillis, false);
	}

	if (eventHandler.spaceFlag)
		physics->Brake(dtMillis);

	//debug commands
	if (eventHandler.wFlag)
		physics->DBG_Slide(sf::Vector2f(0.0f, -1.0f), dtMillis);

	if (eventHandler.sFlag)
		physics->DBG_Slide(sf::Vector2f(0.0f, 1.0f), dtMillis);

	if (eventHandler.aFlag)
		physics->DBG_Slide(sf::Vector2f(-1.0f, 0.0f), dtMillis);

	if (eventHandler.dFlag)
		physics->DBG_Slide(sf::Vector2f(1.0f, 0.0f), dtMillis);

}