#include <vector>

#include "WorldSpaceManager.h"
#include "../Entities/Entity.h"
#include "MathCommon.h"

extern const int screenLen, screenHeight;
std::vector<Entity*> G_STATICOBJECTS;
std::vector<Entity*> G_VARIABLEOBJECTS;

WorldSpaceManager::WorldSpaceManager()
{
	//determine cell width and height
	cellWidth = screenLen / 10.0f;
	cellHeight = screenHeight / 10.0f;

	//there will always be 100 cells in the world
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			cells[i][j] = sf::RectangleShape(sf::Vector2f(cellWidth, cellHeight));
			cells[i][j].setFillColor(sf::Color(255, 165, 0, 150));
			cells[i][j].setPosition(sf::Vector2f(i*cellWidth, j*cellHeight));			
		}
	}


	for (int i = 0; i < 100; i++) {

	}
}


WorldSpaceManager::~WorldSpaceManager()
{
}

void WorldSpaceManager::UpdateAllEntitiesInCollSpace()
{
	for (auto entity : G_STATICOBJECTS) {
		AddEntityToCollisionSpace(entity);
	}

	for (auto entity : G_VARIABLEOBJECTS) {
		AddEntityToCollisionSpace(entity);
	}
}

void WorldSpaceManager::UpdateVariableEntitiesInCollSpace()
{
	for (auto entity : G_VARIABLEOBJECTS) {
		AddEntityToCollisionSpace(entity);
	}
}

void WorldSpaceManager::AddEntityToCollisionSpace(Entity* entity)
{
	std::vector<sf::Vector2i> pairs;

	auto worldCorners = entity->GetWorldCorners();

	if (worldCorners != nullptr) {

		auto coords = GetCollisionSpaceCoords(std::vector<sf::Vector2f>(std::begin(*worldCorners), std::end(*worldCorners)));

		for (auto coord : coords) {
			worldSpace[coord.x][coord.y].push_back(entity);
		}
	}
}

sf::Vector2i WorldSpaceManager::ConvertPointToCellCoords(const sf::Vector2f& point) const
{
	//yes, this will lose all the decimal points, but that's what I want
	return sf::Vector2i(point.x/cellWidth, point.y/cellHeight);
}

//this function is public because it's used by the new physics state to 
//determine its location and compute possible collision
std::vector<sf::Vector2i> WorldSpaceManager::GetCollisionSpaceCoords(const std::vector<sf::Vector2f>& worldCorners) const
{
	std::vector<sf::Vector2i> pairs;

	if (worldCorners.size() == 0)
		return pairs;

	if (worldCorners.size() == 1)
	{
		pairs.push_back(ConvertPointToCellCoords(worldCorners[0]));
		return pairs;
	}

	//first, determine leftest, highest, rightest, lowest point for entire shape
	//then determine square of cells that object is encompassed in
	float leftest = worldCorners[0].x;
	float rightest = worldCorners[0].x;
	float highest = worldCorners[0].y;
	float lowest = worldCorners[0].y;

	for (int i = 1; i < worldCorners.size(); i++) {
		if (worldCorners[i].x < leftest)
			leftest = worldCorners[i].x;
		else if (worldCorners[i].x > rightest)
			rightest = worldCorners[i].x;
		if (worldCorners[i].y < lowest)
			lowest = worldCorners[i].y;
		else if (worldCorners[i].y > highest)
			highest = worldCorners[i].y;
	}

	//iterate through every cell and return cells that shape belongs to
	for (int xCell = leftest / cellWidth; xCell < rightest / cellWidth; xCell++) {
		for (int yCell = lowest / cellHeight; yCell < highest / cellHeight; yCell++) {
			
			auto currentCell = sf::Vector2i(xCell, yCell);

			for (int i = 0; i < worldCorners.size(); i++)
			{
				auto shapeCorner = worldCorners[i];

				//no collision detection if outside world space
				if (shapeCorner.x < 0.0f || shapeCorner.x > screenLen)
					continue;
				if (shapeCorner.y < 0.0f || shapeCorner.y >screenHeight)
					continue;

				auto cornerCell = ConvertPointToCellCoords(shapeCorner);

				//corner is within current cell
				if (currentCell.x == cornerCell.x && currentCell.y == cornerCell.y)
				{
					AddToVectorNoDuplicates(pairs, currentCell);
					break;
				}

				std::vector<sf::Vector2f> currentCellCorners = {
					sf::Vector2f(currentCell.x*cellWidth, currentCell.y*cellHeight),
					sf::Vector2f(currentCell.x*cellWidth + cellWidth, currentCell.y*cellHeight),
					sf::Vector2f(currentCell.x*cellWidth + cellWidth, currentCell.y*cellHeight + cellHeight),
					sf::Vector2f(currentCell.x*cellWidth, currentCell.y*cellHeight + cellHeight)
				};

				//corner not within current cell, therefore do line intersection test
				if (worldCorners.size() > 1) {

					if (MathCommon::AreColliding(worldCorners, currentCellCorners))
					{
						AddToVectorNoDuplicates(pairs, currentCell);
						break;
					}					
				}
			}
		}
	}

	return pairs;
}

//todo exception thrown when exiting bounds of world
std::vector<Entity*> WorldSpaceManager::GetEntitiesAtCoords(const std::vector<sf::Vector2i>& coords) const
{
	std::vector<Entity*> entitiesToRet = std::vector<Entity*>();
	for (auto coord : coords) {
		for (auto entityToAdd : worldSpace[coord.x][coord.y]) {
			AddToVectorNoDuplicates(entitiesToRet, entityToAdd);
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

void WorldSpaceManager::ClearVariableEntities() {
	for (auto entity : G_VARIABLEOBJECTS) {
		auto coords = entity->GetPrevCollisionSpaceCoords();

		for (auto coord : *coords) {
			worldSpace[coord.x][coord.y].remove(entity);
		}
	}
}

void WorldSpaceManager::DBG_Draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (!worldSpace[i][j].empty())
			{				
				window.draw(cells[i][j]);
			}
		}
	}
}
