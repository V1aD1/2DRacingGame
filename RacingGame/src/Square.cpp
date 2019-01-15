#include "include/Square.h"



Square::Square(float sideLen, sf::Vector2f position)
{
	shape = sf::RectangleShape(sf::Vector2f(sideLen, sideLen));
	shape.setOrigin(sideLen / 2, sideLen / 2);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::Red);
}


Square::~Square()
{
}
