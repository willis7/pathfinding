/* All working correct with linked queue, now need to implement back tracking*/

#include <iostream>
#include <GL/glut.h>
#include "Linkedstack.h"
#include "LinkedQueue.h"
#include "imageloader.h"

using namespace std;

//// WINDOW PROPERTIES /////////////////
int winWidth  = 800;
int winHeight = 800;

//// GLOBALS ///////////////////////////

bool found= false;

int col= 1;
int row= 2;
const int ROWMAX = 11;
const int COLMAX = 16;
int tempx;
int tempy; 

int objects = 3;
int count;

GLuint textureId;				//The id of the texture
//Linkedstack RenderList;			//Creates a render list for creating spheres
LinkedQueue RenderList;
LinkedQueue ObjPositions;

char maze[ROWMAX][COLMAX] =
{
{'B','B','B','B','B','B','B','B','B','B','B','B',' B','B','B','B'},
{'B','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B'},
{'B','B','B','B','B','B','B','B','B','B',' ','B','B','B',' ','B'},
{'B',' ',' ',' ',' ',' ',' ',' ',' ','B','F','B',' ','B',' ','B'},
{'B','B','B','B','B','B','B','B',' ','B','B','B',' ','B',' ','B'},
{'B',' ',' ',' ',' ',' ',' ','B',' ',' ',' ',' ',' ','B',' ','B'},
{'B','B','B','B','B','B','B','B',' ','B','B','B','B','B',' ','B'},
{'B','F',' ',' ','B',' ',' ',' ',' ','B',' ',' ',' ',' ',' ','B'},
{'B','B','B',' ',' ',' ',' ',' ','B','B','B','B',' ','B','B','B'},
{'B','F',' ',' ','B','B','B',' ',' ',' ',' ',' ',' ',' ',' ','B'},
{'B','B','B','B','B','B','B','B','B','B','B','B',' B','B','B','B'}
};

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);				 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);	 //Tell OpenGL which texture to edit

	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,					 //Always GL_TEXTURE_2D
				 0,								 //0 for now
				 GL_RGB,						 //Format OpenGL uses for image
				 image->width, image->height,	 //Width and height
				 0,								 //The border of the image
				 GL_RGB,						 //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,				 //GL_UNSIGNED_BYTE, because pixels are stored
												 //as unsigned numbers
				 image->pixels);				 //The actual pixel data

	return textureId; //Returns the id of the texture
}


void initGL()
{
	glEnable(GL_DEPTH_TEST);

	Image* image = loadBMP("crate.bmp");
	textureId = loadTexture(image);
	delete image;
	
}
void runMaze()
{
	Linkedstack MazeList;			//creates a new empty list

	MazeList.push(1,1);				//push starting position

	int currentx, currenty;
	currentx = MazeList.getNodeX();
	currenty = MazeList.getNodeY();

	while((count != objects)&&(MazeList.endOfList() != true))		
	{
		MazeList.pop();

		if(maze[currentx][currenty] == ' '||maze[currentx][currenty] == 'S'||maze[currentx][currenty] == 'F')
			{
				if(maze[currentx][currenty] == 'F')
				{
					count++;														
					ObjPositions.addToList(currentx, currenty);		
					cout << currentx << endl << currenty << endl; 
				}

				RenderList.addToList(currentx,currenty);								
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

	}
}

void printMaze()												//Handles the drawing of the maze using polygons					
{
	for(int row = 0; row < ROWMAX;row++)
	{
		for(int col = 0; col < COLMAX;col++)
		{		
			if(maze[row][col] == 'B')
			{			
				glBegin(GL_QUADS);									
					
					glTexCoord2f(1.0f, 1.0f);glVertex3f(col+1,row  ,2.0f);				// Top Right Of The Quad (Top)
					glTexCoord2f(1.0f, 0.0f);glVertex3f(col  ,row  ,2.0f);					// Top Left Of The Quad (Top)
					glTexCoord2f(0.0f, 0.0f);glVertex3f(col  ,row+1,2.0f);				// Bottom Left Of The Quad (Top)
					glTexCoord2f(0.0f, 1.0f);glVertex3f(col+1,row+1,2.0f);				// Bottom Right Of The Quad (Top)

					glTexCoord2f(1.0f, 1.0f);glVertex3f(col+1,row+1,1.0f);				// Top Right Of The Quad (Bottom)
					glTexCoord2f(1.0f, 0.0f);glVertex3f(col  ,row+1,1.0f);					// Top Left Of The Quad (Bottom)
					glTexCoord2f(0.0f, 0.0f);glVertex3f(col  ,row  ,1.0f);						// Bottom Left Of The Quad (Bottom)
					glTexCoord2f(0.0f, 1.0f);glVertex3f(col+1,row  ,1.0f);					// Bottom Right Of The Quad (Bottom)

					glTexCoord2f(1.0f, 1.0f);glVertex3f(col,row+1,2.0f);				// Top Right Of The Quad (Left)
					glTexCoord2f(1.0f, 0.0f);glVertex3f(col,row  ,2.0f);					// Top Left Of The Quad (Left)
					glTexCoord2f(0.0f, 0.0f);glVertex3f(col,row  ,1.0f);						// Bottom Left Of The Quad (Left)
					glTexCoord2f(0.0f, 1.0f);glVertex3f(col,row+1,1.0f);					// Bottom Right Of The Quad (Left)

					glTexCoord2f(1.0f, 1.0f);glVertex3f(col+1,row  ,2.0f);				// Top Right Of The Quad (Right)
					glTexCoord2f(1.0f, 0.0f);glVertex3f(col+1,row+1,2.0f);				// Top Left Of The Quad (Right)
					glTexCoord2f(0.0f, 0.0f);glVertex3f(col+1,row+1,1.0f);				// Bottom Left Of The Quad (Right)
					glTexCoord2f(0.0f, 1.0f);glVertex3f(col+1,row  ,1.0f);					// Bottom Right Of The Quad (Right)

					glTexCoord2f(1.0f, 1.0f);glVertex3f(col+1,row+1,2.0f);				// Top Right Of The Quad (Front)
					glTexCoord2f(1.0f, 0.0f);glVertex3f(col ,row+1, 2.0f);				// Top Left Of The Quad (Front)
					glTexCoord2f(0.0f, 0.0f);glVertex3f(col ,row+1, 1.0f);					// Bottom Left Of The Quad (Front)
					glTexCoord2f(0.0f, 1.0f);glVertex3f(col+1,row+1,1.0f);				// Bottom Right Of The Quad (Front)

					glTexCoord2f(1.0f, 1.0f);glVertex3f(col+1,row,1.0f);					// Top Right Of The Quad (Back)
					glTexCoord2f(1.0f, 0.0f);glVertex3f(col  ,row,1.0f);						// Top Left Of The Quad (Back)
					glTexCoord2f(0.0f, 0.0f);glVertex3f(col  ,row,2.0f);					// Bottom Left Of The Quad (Back)
					glTexCoord2f(0.0f, 1.0f);glVertex3f(col+1,row,2.0f);				// Bottom Right Of The Quad (Back)

				glEnd();
			}		
		}
	}
}

void exitGL(int returnCode)
{
	exit(returnCode);
}

//// DISPLAY CALLBACK /////////////////////
void drawScene()
{
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-8.0f,-5.0f, -20.0f);			// sets the translate for the maze

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);

	printMaze();

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
			
			glTranslatef(tempy+0.5,tempx+0.5,1.5f);		// sets up new translate for sphere
			glColor3f(0.0f,0.0f,1.0f);					// Set The Color To Yellow
			glutWireSphere(0.25,20,20);

	glPopMatrix();

	glutSwapBuffers();
}

void handleResize(int width,int height)
{
	winWidth  = width;
	winHeight = height;
	glViewport(0,0,width,height);

	// set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);

	// switch back to modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress(unsigned char key,int x,int y)
{
	if (key == 27) exit(0);
}

void update(int value)
{
	
	tempx = RenderList.getNodeX();
	tempy = RenderList.getNodeY();

	RenderList.removeFromList();

	glutPostRedisplay(); //Tell GLUT that the scene has changed
    
    //Tell GLUT to call update again in 1000 milliseconds
	glutTimerFunc(500, update, 0);
}

//// MAIN PROGRAM //////////////////////
int main(int argc,char **argv)
{
	runMaze();
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(winWidth,winHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Dungeon Search");


	glutDisplayFunc(drawScene);
	glutTimerFunc(500, update, 0);									 //Adds a timer in order to update the sphere's location gradually
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(handleKeypress);
	
	initGL();
	glutMainLoop();
	exitGL(0);

	return 0;
}