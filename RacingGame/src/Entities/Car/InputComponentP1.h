#pragma once

#include "../../Components/InputComponent.h"

class InputComponentP1 : public InputComponent
{
public:
	InputComponentP1();
	~InputComponentP1();

public:
	virtual void Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) override;
};

