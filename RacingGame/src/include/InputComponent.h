#pragma once
#include "ConvexEntity.h"
#include "EventHandler.h"

class InputComponent
{
public:
	virtual void Update(ConvexEntity& car, EventHandler& eventHandler, float dtMillis) = 0;

	virtual ~InputComponent(){}
};

