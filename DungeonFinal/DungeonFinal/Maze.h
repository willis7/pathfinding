#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"


class Maze
{
private:

	char** dungeonMap;
	int COLMAX;
	int ROWMAX;
	int numObjects;

	GLuint textureId;

public:

	Maze();
	~Maze();

	void loadMaze(char *filename);
	void printMaze();

	char** getMap();
	int getNumObjects();

	GLuint loadTexture(Image* image);
	GLuint getTextureId();

};

