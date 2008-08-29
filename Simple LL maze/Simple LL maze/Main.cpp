#include"Linkedstack.h"
#include<iostream>
#include"stdlib.h"
using namespace std;

bool found= false;
int row = 1;
int col = 2;
const int ROWMAX = 11;
const int COLMAX = 16;

char maze[ROWMAX][COLMAX] =
{
{'B','B','B','B','B','B','B','B','B','B','B','B',' B','B','B','B'},
{'B','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B'},
{'B','B','B','B','B','B','B','B','B','B',' ','B','B','B',' ','B'},
{'B','F',' ',' ',' ',' ',' ',' ',' ','B',' ','B',' ','B',' ','B'},
{'B','B','B','B','B','B','B','B',' ','B','B','B',' ','B',' ','B'},
{'B',' ',' ',' ',' ',' ',' ','B',' ',' ',' ',' ',' ','B',' ','B'},
{'B','B','B','B','B','B','B','B',' ','B','B','B','B','B',' ','B'},
{'B',' ',' ',' ','B','B','B',' ',' ','B',' ',' ',' ',' ',' ','B'},
{'B','B','B',' ',' ',' ',' ',' ','B','B','B','B',' ','B','B','B'},
{'B',' ',' ',' ','B','B','B',' ',' ',' ',' ',' ',' ',' ',' ','B'},
{'B','B','B','B','B','B','B','B','B','B','B','B',' B','B','B','B'}
};

void printMaze();		//funtion prototype


void main(void)
{
	printMaze();

	Linkedstack MazeList;			//creates a new empty list

	MazeList.push(1,1);				//push starting position

	int currentx, currenty;
	currentx = MazeList.getNodeX();
	currenty = MazeList.getNodeY();


	while((!found)&&(MazeList.endOfList() != true))
	{
		MazeList.pop();

		if(maze[currentx][currenty] == 'F')
		{
			found = true;
		}
		else if(maze[currentx][currenty] == ' '||maze[currentx][currenty] == 'S')
			{
				maze[currentx][currenty] = '*';
			}

			if(maze[currentx][currenty+1]== ' '||maze[currentx][currenty+1] == 'F')		//North
			{
				MazeList.push(currentx,currenty);
				MazeList.push(currentx,currenty+1);
			}
			else if (maze[currentx][currenty-1]== ' '||maze[currentx][currenty-1] == 'F')	//South
			{
				MazeList.push(currentx, currenty);
				MazeList.push(currentx, currenty-1);
			}
			else if (maze[currentx-1][currenty]== ' '||maze[currentx-1][currenty] == 'F')	//West
			{
				MazeList.push(currentx, currenty);
				MazeList.push(currentx-1, currenty);
			}
			else if (maze[currentx+1][currenty]== ' '||maze[currentx+1][currenty] == 'F')	//East
			{
				MazeList.push(currentx, currenty);
				MazeList.push(currentx+1, currenty);
			}
				
			currentx = MazeList.getNodeX();
			currenty = MazeList.getNodeY();
			
		system("cls");
		printMaze();
	}
	 
		
}
void printMaze()
{
	for(int row = 0; row < ROWMAX;row++)
	{
		for(int col = 0; col < COLMAX;col++)
			cout << maze[row][col];
			cout << endl;
	}
}
