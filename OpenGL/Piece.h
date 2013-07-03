#ifndef PIECE_H_
#define PIECE_H_


#include <GL/glui.h>
#include <math.h>

//using namespace std;

class Piece{

private:
	
	
	int x,y,z,color;

public:
	Piece(int x,int z,int color);
	void buildPiece(GLenum mode,GLUquadric* glQ,int id);
	void setCoords(int x, int z);
	int getX(){return x;}
	int getZ(){return z;}
	int getColor(){return color;}
	

};

#endif