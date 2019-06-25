#include "InputComponentP2.h"
#include "../../Entities/Entity.h"

InputComponentP2::InputComponentP2()
{
}


InputComponentP2::~InputComponentP2()
{
}


void InputComponentP2::Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) {
	PhysicsComponent* physics = entity.m_physics;

	if (eventHandler.upFlagP2)
		physics->Accelerate(dtMillis, true);

	else if (eventHandler.downFlagP2) {
		physics->SetReversingFlag(true);
		physics->Accelerate(dtMillis, false);
	}

	if (!eventHandler.downFlagP2)
		physics->SetReversingFlag(false);

	if(!eventHandler.upFlagP2 && !eventHandler.downFlagP2)
		physics->Decelerate(dtMillis);

	if (eventHandler.leftFlagP2)
		physics->Rotate(dtMillis, true);

	if (eventHandler.rightFlagP2)
		physics->Rotate(dtMillis, false);

	if (eventHandler.brakeFlagP2) {
		physics->SetBrakingFlag(true);
		physics->Brake(entity, dtMillis);
	}

	if (!eventHandler.brakeFlagP2)
		physics->SetBrakingFlag(false);

	//debug commands
	if (eventHandler.tFlag)
		physics->DBG_Slide(entity, sf::Vector2f(0.0f, -1.0f), dtMillis);

	if (eventHandler.gFlag)
		physics->DBG_Slide(entity, sf::Vector2f(0.0f, 1.0f), dtMillis);

	if (eventHandler.fFlag)
		physics->DBG_Slide(entity, sf::Vector2f(-1.0f, 0.0f), dtMillis);

	if (eventHandler.hFlag)
		physics->DBG_Slide(entity, sf::Vector2f(1.0f, 0.0f), dtMillis);
}