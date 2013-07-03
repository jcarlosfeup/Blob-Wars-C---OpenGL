#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <cmath>
#include <GL/glui.h>
#define VLENGTH 3


using namespace std;

class Board{


public:
	Board (int dimension);
	~Board(){};
	void drawBoard(GLenum mode);
	void paralelo(GLdouble dimx, GLdouble dimy, GLdouble dimz);
	void newellSquare(GLdouble *vec1,GLdouble *vec2,GLdouble *vec3,GLdouble *vec4,GLdouble *normal);
	void normalise(GLdouble *vec);
	void hitZone(GLenum mode, int x, int z);

private:
	int dimension;

};

#endif