#pragma once
#include "EventHandler.h"

class Car;

class InputComponent
{
public:
	InputComponent();
	~InputComponent();
	virtual void Update(Car& car, const EventHandler& eventHandler, float dtMillis);
};

