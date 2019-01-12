#pragma once
class EventHandler
{
public:
	EventHandler();

	static void HandleResize(int width, int height);
	static void HandleInput();

	~EventHandler();
};

