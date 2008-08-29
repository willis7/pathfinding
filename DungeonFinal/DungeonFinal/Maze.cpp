#include "Maze.h"

Maze::Maze()
{
	Image* image = loadBMP("crate.bmp");
	textureId = loadTexture(image);
	delete image;
}
void Maze::loadMaze(char *filename)
{
	char **myMaze;
	char temp;

	FILE *f;
	int rows, objects, cols;

	f = fopen(filename,"r");
	
	if(f == NULL)
	{
		printf( "The file was not opened\n" );
	}
	else
	{
		fscanf_s(f,"%d",&objects);		//gets number of objects in maze
		fscanf_s(f,"%d",&rows);			//gets how many rows
		fscanf_s(f,"%d",&cols);			//cols

		numObjects = objects;
		ROWMAX = rows;
		COLMAX = cols;

		myMaze = (char**)malloc(sizeof(char*)*rows);

		for(int i = 0; i < rows; i++)
		{
			myMaze[i] = (char*)malloc(sizeof(char)*cols);
			for(int j = 0; j < cols; j++)
			{
				fscanf_s(f,"%c",&temp);
				if(temp!='\n')
				{
					myMaze[i][j] = temp;
					
				}
				else
					j--;
			}
		}
		
		dungeonMap = myMaze;

		
		/*for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				printf("%c",myMaze[i][j]);
			}
			printf("\n");
		}           //Maze print test */
		
	}
}

Maze::~Maze()
{
	delete(dungeonMap);
}

void Maze::printMaze()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for(int row = 0; row < ROWMAX;row++)
	{
		for(int col = 0; col < COLMAX;col++)
		{		
			if(dungeonMap[row][col] == 'B')
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
char** Maze::getMap()
{
	return dungeonMap;
}
int Maze::getNumObjects()
{
	return numObjects;
}

GLuint Maze::loadTexture(Image *image)
{
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
GLuint Maze::getTextureId()
{
	return textureId;
}