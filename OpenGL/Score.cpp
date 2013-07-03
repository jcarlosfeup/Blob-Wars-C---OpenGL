#include "Score.h"

Score::Score(){

	score = 0;
	time = 0;
}

	
void Score::updateScore(int new_score){

	score = new_score;
}
	

void Score::buildBoardScore(){

	int dimX = 6.0;
	int dimY = 6.0;
	int dimZ = 1.0;

	vector<int> pontuacao(3,0);
	parserScore(pontuacao);

	vector<int> time(2,0);
	parserTime(time);

	glEnable(GL_COLOR_MATERIAL);
	//glColor3f(0.2,0.5,0.7);
	glColor3f(0.9,0.9,0.9);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,10);
	//Face frente (dividida em 4 partes)
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(0.0,dimY-(dimY/4),dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,dimY-(dimY/4),dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(0.0,dimY,dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//Numero de pontos, divido em 3 partes
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,pontuacao[2]);
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(0.0,dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX-(dimX/3)*2,dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX-(dimX/3)*2,dimY-(dimY/4),dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(0.0,dimY-(dimY/4),dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,pontuacao[1]);
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(dimX-(dimX/3)*2,dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX-(dimX/3),dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX-(dimX/3),dimY-(dimY/4),dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX-(dimX/3)*2,dimY-(dimY/4),dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,pontuacao[0]);
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0);glVertex3d(dimX-(dimX/3),dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY-(dimY/4),dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(dimX-(dimX/3),dimY-(dimY/4),dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	/**************************************************************/
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,11);
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,dimY-(dimY/4)*3,dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(0.0,dimY-(dimY/4)*3,dimZ);
		glTexCoord2f(0.0,1.0);glVertex3d(0.0,dimY-(dimY/4)*2,dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY-(dimY/4)*2,dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,time[1]);
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0); glVertex3d(0.0,0.0,dimZ);
		glTexCoord2f(1.0,0.0); glVertex3d(dimX-(dimX/2),0.0,dimZ);
		glTexCoord2f(1.0,1.0); glVertex3d(dimX-(dimX/2),dimY-(dimY/4)*3,dimZ);
		glTexCoord2f(0.0,1.0); glVertex3d(0.0,dimY-(dimY/4)*3,dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,time[0]);
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0); glVertex3d(dimX-(dimX/2),0.0,dimZ);
		glTexCoord2f(1.0,0.0); glVertex3d(dimX,0.0,dimZ);
		glTexCoord2f(1.0,1.0); glVertex3d(dimX,dimY-(dimY/4)*3,dimZ);
		glTexCoord2f(0.0,1.0); glVertex3d(dimX-(dimX/2),dimY-(dimY/4)*3,dimZ);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	//Lado esquerdo
	glBegin(GL_POLYGON);
	    glNormal3d(-1.0,0.0,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,0.0,dimZ);
		glVertex3d(0.0,dimY,dimZ);
		glVertex3d(0.0,dimY,0.0);
	glEnd();

	//Lado direito
	glBegin(GL_POLYGON);
	    glNormal3d(1.0,0.0,0.0);
		glVertex3d(dimX,0.0,0.0);
		glVertex3d(dimX,0.0,dimZ);
		glVertex3d(dimX,dimY,dimZ);
		glVertex3d(dimX,dimY,0.0);
	glEnd();

	//Atrás
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,0.0,-1.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(dimX,0.0,0.0);
		glVertex3d(dimX,dimY,0.0);
		glVertex3d(0.0,dimY,0.0);
	glEnd();

	//Topo
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,1.0,0.0);
		glVertex3d(0.0,dimY,dimZ);
		glVertex3d(dimX,dimY,dimZ);
		glVertex3d(dimX,dimY,0.0);
		glVertex3d(0.0,dimY,0.0);
	glEnd();

	//Baixo
	glBegin(GL_POLYGON);
	    glNormal3d(0.0,-1.0,0.0);
		glVertex3d(0.0,0.0,dimZ);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(dimX,0.0,0.0);
		glVertex3d(dimX,0.0,dimZ);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
}

void Score::parserScore(vector<int> &pont){

	int qqcoisa = this->score;

	pont[0] = qqcoisa % 10;
	qqcoisa /= 10;
	pont[1] = qqcoisa % 10;
	qqcoisa /= 10;
	pont[2] = qqcoisa % 10;
}

void Score::parserTime(vector<int> &time){

	int qqcoisa = this->time;

	time[0] = qqcoisa % 10;
	qqcoisa /= 10;
	time[1] = qqcoisa % 10;
}