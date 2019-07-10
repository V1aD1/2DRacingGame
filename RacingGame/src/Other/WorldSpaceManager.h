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
	static const int c_worldSpace_x_cell_count = 10;
	static const int c_worldSpace_y_cell_count = 10;

public:
	WorldSpaceManager();
	~WorldSpaceManager();

	void UpdateAllEntitiesInCollSpace();
	void UpdateVariableEntitiesInCollSpace();

	void AddEntityToCollisionSpace(Entity* entity);

	std::vector<sf::Vector2i> GetCollisionSpaceCoords(const std::vector<sf::Vector2f>& worldCorners) const;
	std::vector<Entity*> GetEntitiesAtCoords(const std::vector<sf::Vector2i>& coords) const;
	void ClearWorldSpace();
	void ClearVariableEntities();
	void DBG_Draw(sf::RenderWindow& window);

private:
	template <typename T>
	static void AddToVectorNoDuplicates(std::vector<T>& vec, T val);
	sf::Vector2i ConvertPointToCellCoords(const sf::Vector2f& point) const;

private:
	//world space will always be divided into 100 cells
	std::list<Entity*> worldSpace[c_worldSpace_x_cell_count][c_worldSpace_y_cell_count];
	sf::RectangleShape cells [c_worldSpace_y_cell_count][c_worldSpace_y_cell_count];
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
