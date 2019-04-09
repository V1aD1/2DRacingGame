#pragma once
#include <array>
#include <list>
#include <utility>
#include <SFML/Graphics.hpp>

class Entity;

class WorldSpaceManager
{
private:
	float cellWidth;
	float cellHeight;

public:
	WorldSpaceManager();
	~WorldSpaceManager();

	void UpdateAllEntitiesInCollSpace();
	void UpdateVariableEntitiesInCollSpace();

	void AddEntityToCollisionSpace(const Entity* entity);
	std::vector<sf::Vector2i> GetCollisionSpaceCoords(const std::vector<sf::Vector2f>& worldCorners);
	std::vector<const Entity*> GetEntitiesAtCoords(const std::vector<sf::Vector2i>* coords);
	void ClearWorldSpace();
	void ClearVariableEntities();
	void DBG_Draw(sf::RenderWindow& window);

private:
	template <typename T>
	static void AddToVectorNoDuplicates(std::vector<T>& vec, T val);
	static bool CheckLineCollision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);
	sf::Vector2i ConvertPointToCellCoords(sf::Vector2f point);

	//world space will always be divided into 100 cells
	std::list<const Entity*> worldSpace[10][10];
};

template<typename T>
inline void WorldSpaceManager::AddToVectorNoDuplicates(std::vector<T>& vals, T valToAdd)
{
	bool alreadyAdded = false;
	
	//todo order so as to avoid this inneficiency?
	for (auto val : vals)
	{
		if (val == valToAdd) {
			alreadyAdded = true;
			break;
		}
	}

	//to ensure value isn't added twice
	if (!alreadyAdded) {
		vals.push_back(valToAdd);
	}
}
