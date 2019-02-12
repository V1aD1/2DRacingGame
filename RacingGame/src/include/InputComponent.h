#pragma once
#include "EventHandler.h"

class Car;

class InputComponent
{
public:
	virtual void Update(Car& car, EventHandler& eventHandler, float dtMillis);
};

