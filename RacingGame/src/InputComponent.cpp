#include "include/InputComponent.h"
#include "include/Car.h"

void InputComponent::Update(Car& car, EventHandler& eventHandler, float dtMillis) {
	if (eventHandler.upFlag)
		car.Accelerate(dtMillis, true);

	if (eventHandler.downFlag)
		car.Accelerate(dtMillis, false);

	if (eventHandler.leftFlag)
		car.Rotate(dtMillis, true);

	if (eventHandler.rightFlag)
		car.Rotate(dtMillis, false);

	if (eventHandler.spaceFlag)
		car.Brake(dtMillis);

	//debug commands
	if (eventHandler.wFlag)
		car.DBG_Slide(sf::Vector2f(0.0f, -1.0f), dtMillis);

	if (eventHandler.sFlag)
		car.DBG_Slide(sf::Vector2f(0.0f, 1.0f), dtMillis);

	if (eventHandler.aFlag)
		car.DBG_Slide(sf::Vector2f(-1.0f, 0.0f), dtMillis);

	if (eventHandler.dFlag)
		car.DBG_Slide(sf::Vector2f(1.0f, 0.0f), dtMillis);

}