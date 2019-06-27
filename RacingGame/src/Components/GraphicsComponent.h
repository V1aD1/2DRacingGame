#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class GraphicsComponent
{
public:
	GraphicsComponent();
	GraphicsComponent(sf::Shape* shape);
	GraphicsComponent(sf::Sprite* sprite);
	virtual ~GraphicsComponent();

	virtual void Update(Entity& entity, sf::RenderWindow& window, float dtTimeMilli) = 0;
	
	sf::Shape* GetShape() const;
	virtual void Enable();

	void SetAlphaChangeRate(float newAlphaChangeRate);
	void SetScaleChangeRate(float newScaleChangeRate);

protected:
	sf::Shape* m_shape;
	sf::Sprite* m_sprite;
	float m_alphaChangeRate = 0;
	float m_scaleChangeRate = 0;
};

