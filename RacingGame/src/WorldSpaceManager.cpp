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

void WorldSpaceManager::AddPairToPairsNoDuplicates(std::vector<sf::Vector2i>& pairs, int x, int y)
{
	bool alreadyAdded = false;
	//todo order so as to avoid this inneficiency?
	for (auto pair : pairs)
	{
		if (pair.x == x && pair.y == y) {
			alreadyAdded = true;
			break;
		}
	}

	//to ensure entity isn't added to the same cell twice
	if (!alreadyAdded) {
		pairs.push_back(sf::Vector2i(x, y));
	}
}


std::vector<sf::Vector2i> WorldSpaceManager::GetCollisionSpaceCoords2(const std::array<sf::Vector2f, 4>* worldCorners)
{
	std::vector<sf::Vector2i> pairs;

	//first, determine leftest, highest, rightest, lowest point for entire shape
	//todo can use float instead of vector2f here
	//todo ignore collision outside of world space
	sf::Vector2f leftest = (*worldCorners)[0];
	sf::Vector2f rightest = (*worldCorners)[0];
	sf::Vector2f highest = (*worldCorners)[0];
	sf::Vector2f lowest = (*worldCorners)[0];
	
	for (int i = 1; i < worldCorners->size(); i++) {
		if ((*worldCorners)[i].x < leftest.x)
			leftest = (*worldCorners)[i];
		else if ((*worldCorners)[i].x > rightest.x)
			rightest = (*worldCorners)[i];
		if ((*worldCorners)[i].y < lowest.y)
			lowest = (*worldCorners)[i];
		else if ((*worldCorners)[i].y > highest.y)
			highest = (*worldCorners)[i];
	}

	//then determine square of cells that object is encompassed in
	//iterate through every cell and return cells that shape belongs to
	//todo create static function that converts point in space to cell location
	for (int xCell = leftest.x / cellWidth; xCell < rightest.x / cellWidth; xCell++) {
		for (int yCell = lowest.y / cellHeight; yCell < highest.y / cellHeight; yCell++) {
			for (auto shapeCorner : *worldCorners)
			{

				//todo figure out why this doesn't work inline...
				int x = shapeCorner.x / cellWidth;
				int y = shapeCorner.y / cellHeight;
				//corner is within current cell
				if (xCell == x && yCell == y)
				{
					AddPairToPairsNoDuplicates(pairs, xCell, yCell);
					continue;
				}

				//corner not within current cell, therefore do line intersection test
			}
		}
	}



	//as per https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
	//vectors will be represented by p + r,
	//where p = startpoint, r = endpoint - startpoint

	//you'll be comparing vectors connecting every corner to the next,
	//around the shape, with the 4 sides of each cell that shape may be within
	//vectors are p + r and q + s
	//t = (q - p) x s / (r x s)
	//u = (q - p) x r/(r x s)
	//NOTE: (q - p) and (r x s) used in both equations,
	//so only compute them once!!

	//cases
	//Collinear: if r x s = 0 AND (q - p) x r = 0 (we care)
	//Parallel, non intersecting: r  x s = 0 and (q - p) x r != 0 (don't care)
	//Intersection: if r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
	//Else, lines are not parallel BUT do NOT intersect (don't care)

	//todo once this works, add similar functionality to AddEntityToCollisionSpace()!!

	return pairs;
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

	//each pair now corresponds to a given corner
	//the corners are in a clockwise order

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