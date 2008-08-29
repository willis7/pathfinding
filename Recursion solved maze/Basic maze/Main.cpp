#include <iostream>
using namespace std;

int col= 1;
int row= 2;
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
{'B',' ',' ',' ','B',' ',' ',' ',' ','B',' ',' ',' ',' ',' ','B'},
{'B','B','B',' ',' ',' ',' ',' ','B','B','B','B',' ','B','B','B'},
{'B',' ',' ',' ','B','B','B',' ',' ',' ',' ',' ',' ',' ',' ','B'},
{'B','B','B','B','B','B','B','B','B','B','B','B',' B','B','B','B'}
};

void printMaze();
void runMaze(int, int);

void printMaze()
{
	for(int row = 0; row < ROWMAX;row++)
	{
		for(int col = 0; col < COLMAX;col++)
			cout << maze[row][col];
			cout << endl;
	}
}

void runMaze(int row, int col)
{
	if((row > 0 && row<ROWMAX) && (col > 0 && col < COLMAX))
	{
		if(maze[row][col] == 'F')
		{
		return;
		}else if(maze[row][col] ==' ')
			{
				maze[row][col] ='*';

				runMaze(row, col+1);
				runMaze(row, col-1);
				runMaze(row-1, col);
				runMaze(row+1, col);
			}
		
	}
	system("cls");
	printMaze();
}


int main()
{
	cout << "maze done" << endl;
	runMaze(1, 2);
	return 0;
}
