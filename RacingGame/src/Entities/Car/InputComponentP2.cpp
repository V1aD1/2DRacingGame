#include "InputComponentP2.h"
#include "../../Entities/Entity.h"

InputComponentP2::InputComponentP2()
{
}


InputComponentP2::~InputComponentP2()
{
}


void InputComponentP2::Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) {
	PhysicsComponentV2* physics = entity.m_physics;

	if (eventHandler.upFlagP2)
		physics->Accelerate(dtMillis, true);

	if (eventHandler.downFlagP2)
		physics->Accelerate(dtMillis, false);

	if (eventHandler.leftFlagP2)
		physics->Rotate(dtMillis, true);

	if (eventHandler.rightFlagP2)
		physics->Rotate(dtMillis, false);

	if (eventHandler.brakeFlagP2)
		physics->Brake(dtMillis);

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