#pragma once
class Car;
class PhysicsComponent;
class GraphicsComponent;
class Entity;
class EventHandler;

class InputComponent
{
public:
	InputComponent();
	~InputComponent();
	virtual void Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) = 0;
};

