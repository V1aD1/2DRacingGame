#pragma once

#include "../../Components/InputComponent.h"

class InputComponentP2 : public InputComponent
{
public:
	InputComponentP2();
	~InputComponentP2();

public:
	virtual void Update(Entity& entity, const EventHandler& eventHandler, float dtMillis) override;
};

