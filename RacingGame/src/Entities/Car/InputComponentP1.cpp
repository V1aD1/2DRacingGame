#include "InputComponentP1.h"
#include "../Entity.h"

InputComponentP1::InputComponentP1()
{
}


InputComponentP1::~InputComponentP1()
{
}

void InputComponentP1::Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) {
	PhysicsComponent* physics = entity.m_physics;

	if (eventHandler.upFlagP1)
		physics->Accelerate(dtMillis, true);

	else if (eventHandler.downFlagP1)
		physics->Accelerate(dtMillis, false);

	if(!eventHandler.upFlagP1 && !eventHandler.downFlagP1)
		physics->Decelerate(dtMillis);

	if (eventHandler.leftFlagP1)
		physics->Rotate(dtMillis, true);

	if (eventHandler.rightFlagP1)
		physics->Rotate(dtMillis, false);

	if (eventHandler.brakeFlagP1) {
		physics->SetBrakingFlag(true);
		physics->Brake(entity, dtMillis);
	}

	if (!eventHandler.brakeFlagP1)
		physics->SetBrakingFlag(false);

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