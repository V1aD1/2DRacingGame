#include <vector>

#include "include/WorldSpaceManager.h"
#include "include/Entity.h"
#include "include/MathCommon.h"

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
	//this involves not doing a "worldspace.clear()" every frame in main,
	//and instead clearing only variable objects from the cells
	//luckily, every variable object has a list of the cells they occupy,
	//so only clear the VARIABLE objects from those cells
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

	auto coords = GetCollisionSpaceCoords(std::vector<sf::Vector2f>(std::begin(worldCorners), std::end(worldCorners)));

	for (auto coord : coords) {
		worldSpace[coord.x][coord.y].push_back(entity);
	}
}

bool WorldSpaceManager::CheckLineCollision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
	//as per https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
	//vectors will be represented by a start point (p, q) and end point (p+r, q+s),
	//where r or s = endpoint - startpoint

	auto r = p2 - p1;
	auto s = q2 - q1;

	//you'll be comparing vectors connecting every corner to the next,
	//around the shape, with the 4 sides of each cell that shape may be within
	//vectors are p + r and q + s
	//t = (q - p) x s / (r x s)
	//u = (q - p) x r/(r x s)
	//NOTE: (q - p) and (r x s) used in both equations,
	//so only compute them once!!

	auto QMinP = q1 - p1;
	auto RCrossS = MathCommon::CrossProduct(r, s);

	//Collinear: if r x s = 0 AND (q - p) x r = 0 (we care)
	if (RCrossS == 0.0f && MathCommon::CrossProduct(QMinP, r) == 0) {
		return true;
	}

	//Intersection: if r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
	else if (RCrossS != 0.0f) {
		auto t = MathCommon::CrossProduct(QMinP, s) / RCrossS;
		auto u = MathCommon::CrossProduct(QMinP, r) / RCrossS;

		if (0.0f <= t && t <= 1.0f && 0.0f <= u && u <= 1.0f)
		{
			return true;
		}
	}

	//Parallel, non intersecting: r  x s = 0 and (q - p) x r != 0 (don't care)

	//Else, lines are not parallel BUT do NOT intersect (don't care)

	return false;
}

sf::Vector2i WorldSpaceManager::ConvertPointToCellCoords(sf::Vector2f point)
{
	//yes, this will lose all the decimal points, but that's what I want
	return sf::Vector2i(point.x/cellWidth, point.y/cellHeight);
}

//this function is public because it's used by the new physics state to 
//determine its location and compute possible collision
std::vector<sf::Vector2i> WorldSpaceManager::GetCollisionSpaceCoords(const std::vector<sf::Vector2f>& worldCorners)
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

	//then determine square of cells that object is encompassed in
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

				//corner not within current cell, therefore do line intersection test
				//todo these 4 operations could be done in parallel?
				if (worldCorners.size() > 1) {

					auto nextShapeCorner = (i == (worldCorners.size() - 1)) ? worldCorners[0] : worldCorners[i + 1];


					//checking lines that make up cell in counter clockwise
					if (CheckLineCollision(sf::Vector2f(currentCell.x*cellWidth, currentCell.y*cellHeight),
						sf::Vector2f(currentCell.x*cellWidth + cellWidth, currentCell.y*cellHeight),
						shapeCorner,
						nextShapeCorner) == true)
					{
						//corner is within current cell
						AddToVectorNoDuplicates(pairs, currentCell);
						break;
					}

					else if (CheckLineCollision(sf::Vector2f(currentCell.x*cellWidth + cellWidth, currentCell.y*cellHeight),
						sf::Vector2f(currentCell.x*cellWidth + cellWidth, currentCell.y*cellHeight + cellHeight),
						shapeCorner,
						nextShapeCorner) == true)
					{
						//corner is within current cell
						AddToVectorNoDuplicates(pairs, currentCell);
						break;
					}

					else if (CheckLineCollision(sf::Vector2f(currentCell.x*cellWidth + cellWidth, currentCell.y*cellHeight + cellHeight),
						sf::Vector2f(currentCell.x*cellWidth, currentCell.y*cellHeight + cellHeight),
						shapeCorner,
						nextShapeCorner) == true)
					{
						//corner is within current cell
						AddToVectorNoDuplicates(pairs, currentCell);
						break;
					}

					else if (CheckLineCollision(sf::Vector2f(currentCell.x*cellWidth, currentCell.y*cellHeight + cellHeight),
						sf::Vector2f(currentCell.x*cellWidth, currentCell.y*cellHeight),
						shapeCorner,
						nextShapeCorner) == true)
					{
						//corner is within current cell
						AddToVectorNoDuplicates(pairs, currentCell);
						break;
					}
				}
			}
		}
	}

	return pairs;
}

std::vector<const Entity*> WorldSpaceManager::GetEntitiesAtCoords(const std::vector<sf::Vector2i>* coords)
{
	std::vector<const Entity*> entitiesToRet = std::vector<const Entity*>();
	for (auto coord : *coords) {
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
		//entity.
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
