

#include "Scenario.h"


Scenario::Scenario(){

}
	

void Scenario::buildScenario(int num_cena){

	switch(num_cena){

	//Cena 1 - sala
	case 1:
		cena1();
		break;

	//Cena 2 - natureza
	case 2:
		cena2();
		break;

	//Cena 3 - industria
	case 3:
		cena3();
		break;
	}
}

void Scenario::cena1(){

	int dimX = 30;
	int dimY = 15;
	int dimZ = 20;
	
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,12);
	//"Ch�o" do cen�rio
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);
		glVertex3d(-dimX,0.0,dimZ);
		glTexCoord2f(1.0,1.0);
		glVertex3d(dimX,0.0,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,0.0,-dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,14);
	//Tapete do ch�o
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX/2,0.15,-dimZ/2);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX/2,0.15,dimZ/2);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX/2,0.15,dimZ/2);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX/2,0.15,-dimZ/2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,15);
	//Tapete do ch�o maior
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX/1.8,0.1,-dimZ/1.8);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX/1.8,0.1,dimZ/1.8);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX/1.8,0.1,dimZ/1.8);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX/1.8,0.1,-dimZ/1.8);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,13);
	//Parede tr�s
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,dimY,-dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,dimY,-dimZ);
	glEnd();

	//Parede esquerda
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,dimY,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX,0.0,dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(-dimX,dimY,-dimZ);
	glEnd();

	//Parede direita
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(dimX,dimY,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,dimY,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,0.0,dimZ);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
}


void Scenario::cena2(){

	int dimX = 30;
	int dimY = 15;
	int dimZ = 20;
	
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,16);
	//"Ch�o" do cen�rio
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);
		glVertex3d(-dimX,0.0,dimZ);
		glTexCoord2f(1.0,1.0);
		glVertex3d(dimX,0.0,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,0.0,-dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,19);
	//Tapete do ch�o
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX/2,0.15,-dimZ/2);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX/2,0.15,dimZ/2);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX/2,0.15,dimZ/2);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX/2,0.15,-dimZ/2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,17);
	//Tapete do ch�o maior
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX/1.3,0.1,-dimZ/1.3);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX/1.3,0.1,dimZ/1.3);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX/1.3,0.1,dimZ/1.3);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX/1.3,0.1,-dimZ/1.3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,18);
	//Parede tr�s
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,1.0);glVertex3d(-dimX,dimY,-dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY,-dimZ);
	glEnd();

	//Parede esquerda
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,1.0);glVertex3d(-dimX,dimY,dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,0.0,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(-dimX,dimY,-dimZ);
	glEnd();

	//Parede direita
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,dimY,-dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,0.0,dimZ);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
}

void Scenario::cena3(){

	int dimX = 30;
	int dimY = 15;
	int dimZ = 20;
	
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0,1.0,1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,20);
	//"Ch�o" do cen�rio
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);
		glVertex3d(-dimX,0.0,dimZ);
		glTexCoord2f(1.0,1.0);
		glVertex3d(dimX,0.0,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,0.0,-dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,21);
	//Tapete do ch�o
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX/2,0.15,-dimZ/2);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX/2,0.15,dimZ/2);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX/2,0.15,dimZ/2);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX/2,0.15,-dimZ/2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,23);
	//Tapete do ch�o maior
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX/1.8,0.1,-dimZ/1.8);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX/1.8,0.1,dimZ/1.8);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX/1.8,0.1,dimZ/1.8);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX/1.8,0.1,-dimZ/1.8);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,22);
	//Parede tr�s
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,1.0);glVertex3d(-dimX,dimY,-dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY,-dimZ);
	glEnd();

	//Parede esquerda
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,1.0);glVertex3d(-dimX,dimY,dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,0.0,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(-dimX,dimY,-dimZ);
	glEnd();

	//Parede direita
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX,dimY,-dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,0.0,dimZ);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
}