#include <vector>

#include "include/WorldSpaceManager.h"
#include "include/Entity.h"
extern const int screenLen, screenHeight;
extern std::vector<Entity*> G_STATICOBJECTS;
extern std::vector<Entity*> G_VARIABLEOBJECTS;

WorldSpaceManager::WorldSpaceManager()
{
	//determine cell width and height
	cellWidth = screenLen / 10.0f;
	cellHeight = screenHeight / 10.0f;
}


WorldSpaceManager::~WorldSpaceManager()
{
}

void WorldSpaceManager::PopulateCollisionSpace()
{
	//todo since static objects don't move, 
	//they shouldn't be added and removed from
	//collision space every frame
	for (auto entity : G_STATICOBJECTS) {
		AddEntityToCollisionSpace(entity);
	}

	for (auto entity : G_VARIABLEOBJECTS) {
		AddEntityToCollisionSpace(entity);
	}

}

void WorldSpaceManager::AddEntityToCollisionSpace(const Entity* entity)
{
	std::vector<sf::Vector2i> pairs;

	auto worldCorners = *entity->GetWorldCorners();
	for (auto corner : worldCorners) {

		//no collision detection if outside world space
		if (corner.x < 0.0f || corner.x > screenLen)
			continue;
		if (corner.y < 0.0f || corner.y >screenHeight)
			continue;

		int xCell = corner.x / cellWidth;
		int yCell = corner.y / cellHeight;
		bool alreadyAdded = false;

		for (auto pair : pairs)
		{
			if (pair.x == xCell && pair.y == yCell) {
				alreadyAdded = true;
				break;
			}
		}

		//to ensure entity isn't added to the same cell twice
		if (!alreadyAdded) {
			worldSpace[xCell][yCell].push_back(entity);
			pairs.push_back(sf::Vector2i(xCell, yCell));
		}
	}
}

std::vector<sf::Vector2i> WorldSpaceManager::GetCollisionSpaceCoords(const std::array<sf::Vector2f, 4>* worldCorners)
{
	std::vector<sf::Vector2i> pairs;

	for (auto corner : *worldCorners) {
		//no collision detection if outside world space
		if (corner.x < 0.0f || corner.x > screenLen)
			continue;
		if (corner.y < 0.0f || corner.y >screenHeight)
			continue;

		int xCell = corner.x / cellWidth;
		int yCell = corner.y / cellHeight;
		bool alreadyAdded = false;

		//todo order so as to avoid this inneficiency?
		for (auto pair : pairs)
		{
			if (pair.x == xCell && pair.y == yCell) {
				alreadyAdded = true;
				break;
			}
		}

		//to ensure entity isn't added to the same cell twice
		if (!alreadyAdded) {
			pairs.push_back(sf::Vector2i(xCell, yCell));
		}
	}

	return pairs;
}

//todo should return a UNIQUE list of entities
std::vector<const Entity*> WorldSpaceManager::GetEntitiesAtCoords(const std::vector<sf::Vector2i>* coords)
{
	std::vector<const Entity*> entitiesToRet = std::vector<const Entity*>();
	for (auto coord : *coords) {
		for (auto entityToAdd : worldSpace[coord.x][coord.y]) {

			bool entityAlreadyInList = false;

			//todo sort so as to avoid this inneficiency!
			for (auto entity : entitiesToRet)
			{
				if (entity == entityToAdd)
				{
					entityAlreadyInList = true;
					break;
				}
			}

			if(!entityAlreadyInList)
				entitiesToRet.push_back(entityToAdd);
		}
	}

	return entitiesToRet;
}

void WorldSpaceManager::ClearWorldSpace()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			worldSpace[i][j].clear();
		}
	}
}

void WorldSpaceManager::DBG_Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (!worldSpace[i][j].empty())
			{
				auto shape = sf::RectangleShape(sf::Vector2f(cellWidth, cellHeight));
				shape.setPosition(sf::Vector2f(i*cellWidth, j*cellHeight));
				shape.setFillColor(sf::Color(255, 165, 0, 150));

				window.draw(shape);
			}
		}
	}
}
