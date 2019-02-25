#include "include/InputComponent.h"
#include "include/PhysicsComponent.h"
#include "include/Entity.h"

InputComponent::InputComponent(){}

InputComponent::~InputComponent(){}

void InputComponent::Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) {
	PhysicsComponent* physics = entity.m_physics;

	if (eventHandler.upFlag)
		physics->Accelerate(dtMillis, true);

	if (eventHandler.downFlag)
		physics->Accelerate(dtMillis, false);

	if (eventHandler.leftFlag) 
		physics->Rotate(dtMillis, true);
	
	if (eventHandler.rightFlag) 
		physics->Rotate(dtMillis, false);	

	if (eventHandler.spaceFlag)
		physics->Brake(dtMillis);

	//debug commands
	if (eventHandler.wFlag)
		physics->DBG_Slide(entity, sf::Vector2f(0.0f, -1.0f), dtMillis);

	if (eventHandler.sFlag)
		physics->DBG_Slide(entity, sf::Vector2f(0.0f, 1.0f), dtMillis);

	if (eventHandler.aFlag)
		physics->DBG_Slide(entity, sf::Vector2f(-1.0f, 0.0f), dtMillis);

	if (eventHandler.dFlag)
		physics->DBG_Slide(entity, sf::Vector2f(1.0f, 0.0f), dtMillis);
}