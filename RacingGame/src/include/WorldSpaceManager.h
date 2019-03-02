#pragma once
#include <array>
#include <list>
#include <SFML/Graphics.hpp>

class Entity;

class WorldSpaceManager
{
public:
	WorldSpaceManager();
	~WorldSpaceManager();

	void PopulateCollisionSpace();

	void AddEntityToCollisionSpace(const Entity* entity);
	void ClearWorldSpace();

private:
	//world space will always be divided into 100 cells
	std::list<const Entity*> worldSpace[10][10];
	float cellWidth;
	float cellHeight;
};

