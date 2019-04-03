#pragma once
#include <array>
#include <list>
#include <utility>
#include <SFML/Graphics.hpp>

class Entity;

class WorldSpaceManager
{
public:
	WorldSpaceManager();
	~WorldSpaceManager();

	void PopulateCollisionSpace();

	void AddEntityToCollisionSpace(const Entity* entity);
	std::vector<sf::Vector2i> GetCollisionSpaceCoords(const std::array<sf::Vector2f, 4>* worldCorners);
	std::vector<const Entity*> GetEntitiesAtCoords(const std::vector<sf::Vector2i>* coords);
	void ClearWorldSpace();
	void DBG_Draw(sf::RenderWindow& window);

private:
	static void AddPairToPairsNoDuplicates(std::vector<sf::Vector2i>& pairs, int x, int y);
	static bool CheckLineCollision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);

	//world space will always be divided into 100 cells
	//todo should be list? or vector? or array?
	std::list<const Entity*> worldSpace[10][10];
	float cellWidth;
	float cellHeight;
};

