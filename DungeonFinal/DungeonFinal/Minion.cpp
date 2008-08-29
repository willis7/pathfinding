#include "Minion.h"

void Minion::searchDungeon()
{
	char **maze = dungeon->getMap();
	int numObj = dungeon->getNumObjects();
	
	MazeList.push(1,1);				//push starting position

	int currentx, currenty;
	currentx = MazeList.getNodeX();
	currenty = MazeList.getNodeY();

	while((count != numObj)&&(MazeList.endOfList() !=true))
	{
		MazeList.pop();

		if(maze[currentx][currenty] == 'E'||maze[currentx][currenty] == 'F')
		{
			if(maze[currentx][currenty] == 'F')
			{
				count ++;
				ObjPositions.addToList(currentx, currenty);
			}
			pathway.addToList(currentx, currenty);
			maze[currentx][currenty] = '*';
		}

		if(maze[currentx][currenty+1]== 'E'||maze[currentx][currenty+1] == 'F')		//North
		{
			MazeList.push(currentx,currenty);
			MazeList.push(currentx,currenty+1);
		}
		else if (maze[currentx][currenty-1]== 'E'||maze[currentx][currenty-1] == 'F')	//South
		{
			MazeList.push(currentx, currenty);
			MazeList.push(currentx, currenty-1);
		}
		else if (maze[currentx-1][currenty]== 'E'||maze[currentx-1][currenty] == 'F')	//West
		{
			MazeList.push(currentx, currenty);
			MazeList.push(currentx-1, currenty);
		}
		else if (maze[currentx+1][currenty]== 'E'||maze[currentx+1][currenty] == 'F')	//East
		{
			MazeList.push(currentx, currenty);
			MazeList.push(currentx+1, currenty);
		}
			
		if(MazeList.endOfList() != true)
		{
			currentx = MazeList.getNodeX();
			currenty = MazeList.getNodeY();	
		}
	}

}

Maze* Minion::getMaze()
{
	return dungeon;
}
	
void Minion::setMaze(Maze* m)
{
	dungeon = m;
}
float Minion::getNodeX()
{
	return pathway.getNodeX();
}
float Minion::getNodeY()
{
	return pathway.getNodeY();
}
void Minion::removeFromList()
{
	pathway.removeFromList();
}
bool Minion::endOfList()
{
	return pathway.endOfList();
}
void Minion::printObjects()
{
	ObjPositions.printList();
}
