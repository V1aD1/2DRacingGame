#pragma once

#include <SFML/Graphics.hpp>

class EventHandler
{
public:
	EventHandler();

	void HandleResize(int width, int height);
	void HandleEvent(sf::RenderWindow& window, sf::Event& event);

	bool upFlagP1 = false;
	bool downFlagP1 = false;
	bool leftFlagP1 = false;
	bool rightFlagP1 = false;
	bool brakeFlagP1 = false;

	bool upFlagP2 = false;
	bool downFlagP2 = false;
	bool leftFlagP2 = false;
	bool rightFlagP2 = false;
	bool brakeFlagP2 = false;

	//debug movement for P1
	bool wFlag = false;
	bool sFlag = false;
	bool aFlag = false;
	bool dFlag = false;

	//debug movement for P2
	bool tFlag = false;
	bool gFlag = false;
	bool fFlag = false;
	bool hFlag = false;

	~EventHandler();
};

