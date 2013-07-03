#include "Piece.h"

Piece::Piece(int x,int z,int color){

	this->x = 2*(x-1);
	this->y = 1.6;
	this->z = z*2;
	this->color = color;
}
	
void Piece::buildPiece(GLenum mode,GLUquadric* glQ, int id){

	if (mode == GL_SELECT){
			glLoadName (id);
		}

	glEnable(GL_COLOR_MATERIAL);
	if(color == 1)
		glColor3f(1.0,0.0,0.0);
	else if(color == 2)
		glColor3f(0.0,0.0,1.0);
	
	//Esfera de baixo
	glPushMatrix();
	glTranslated(x,y,z);
	gluSphere(glQ,1.0,16,8);
	glPopMatrix();

	//Esfera de cima
	glPushMatrix();
	glTranslated(x,y*2,z);
	gluSphere(glQ,0.6,16,8);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	
	//Olhos
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glTranslated(x,y+1,z+0.5);
	gluSphere(glQ,0.2,16,8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x+0.5,y+1,z+0.4);
	gluSphere(glQ,0.2,16,8);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);

	//Olhos2
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0,0.0,0.0);
	glPushMatrix();
	glTranslated(x,y+1.0,z+0.7);
	gluSphere(glQ,0.1,16,8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x+0.6,y+1.0,z+0.5);
	gluSphere(glQ,0.1,16,8);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}

void Piece::setCoords(int x, int z){
	this->x = 2*(x-1);
	this->z = z*2;
}

