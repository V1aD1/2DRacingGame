#pragma once
class Car;
class PhysicsComponentV2;
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

