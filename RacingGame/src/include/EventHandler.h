#pragma once

#include <SFML/Graphics.hpp>

class EventHandler
{
public:
	EventHandler();

	void HandleResize(int width, int height);
	void HandleEvent(sf::RenderWindow& window, sf::Event& event);

	bool upFlag = false;
	bool downFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;
	bool spaceFlag = false;

	bool wFlag = false;
	bool sFlag = false;
	bool aFlag = false;
	bool dFlag = false;

	~EventHandler();
};

