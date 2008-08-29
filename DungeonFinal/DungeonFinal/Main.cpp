#include "Maze.h"
#include "Minion.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;

//// WINDOW PROPERTIES /////////////////
int winWidth  = 800;
int winHeight = 800;

// Instatiation of both maze and minion
Maze *dungeon = new Maze();
Minion *golum = new Minion();

void menu(void);

//OpenGL function prototypes
void exitGL(int returnCode);
void drawScene(void);
void handleResize(int width,int height);
void handleKeypress(unsigned char key,int x,int y);
void update(int value);

// Globals for OpenGL to use
int tempx;
int tempy; 
static int count;

int main(int argc,char **argv)
{	
	
	menu();
	golum->setMaze(dungeon);		
	golum->searchDungeon();
	cout << "The objects locations for this maze are: " << endl;
	golum->printObjects();

	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(winWidth,winHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Dungeon Search");

	glutDisplayFunc(drawScene);
	glutTimerFunc(500, update, 0);					
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(handleKeypress);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	exitGL(0);

	return 0;
}
void menu()
{
	unsigned char key;
	cout << "Please enter what size maze you would like to play:" << endl;
	cout << "a: 8x8 \nb: 16x16 3 objects\nc: 16x16 5 objects" << endl; 
	cin >> key;

	switch(key)
	{
		case 'a':
			dungeon->loadMaze("map8.txt");
			break;

		case 'b':
			dungeon->loadMaze("map16a.txt");
			break;

		case 'c':
			dungeon->loadMaze("map16b.txt");
			break;
	}

}

void exitGL(int returnCode)
{
	exit(returnCode);
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-8.0f,-5.0f, -20.0f);			
	glColor3f(1.0f, 1.0f, 1.0f);

	dungeon->printMaze();

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
			glTranslatef(tempy+0.5,tempx+0.5,1.5f);		
			glColor3f(0.0f,0.0f,1.0f);				
			glutWireSphere(0.25,20,20);
	glPopMatrix();

	glutSwapBuffers();
}
void handleResize(int width,int height)
{
	winWidth  = width;
	winHeight = height;
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress(unsigned char key,int x,int y)
{
	if (key == 27) exit(0);
}
void update(int value)
{
		tempx = golum->getNodeX();
		tempy = golum->getNodeY();
		golum->removeFromList();

	glutPostRedisplay();

	glutTimerFunc(500, update, 0);
}
