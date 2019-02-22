#pragma once
#include "EventHandler.h"

class Car;
class PhysicsComponent;
class GraphicsComponent;

class InputComponent
{
public:
	InputComponent();
	~InputComponent();
	virtual void Update(Entity& entity, PhysicsComponent* physics, const EventHandler& eventHandler, float dtMillis);
};

