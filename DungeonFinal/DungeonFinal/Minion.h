#pragma once
#include "Maze.h"
#include "LinkedQueue.h"
#include "Linkedstack.h"

class Minion 
{
private:
	LinkedQueue ObjPositions;
	LinkedQueue pathway;
	Maze* dungeon;

	int count;
	Linkedstack MazeList;

public:
	Maze* getMaze();
	void setMaze(Maze* m);
	void searchDungeon();

	float getNodeY();
	float getNodeX();

	void removeFromList();
	bool endOfList();
	void printObjects();
};
