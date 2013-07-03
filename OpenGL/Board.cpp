#include "Board.h"



Board::Board(int dimension){

	this->dimension = dimension*dimension;
}

/* Function to normalise a vector to unit length */
void Board::normalise(GLdouble *vec)
{
  GLdouble length = 0.0;
  int i;

  for (i=0;i<VLENGTH;i++){
     length += vec[i]*vec[i]; 
  }
  length= (GLdouble) sqrt((double)length); 

  for (i=0;i<VLENGTH;i++){
     vec[i] = vec[i]/length; 
  }
}

void Board::newellSquare(GLdouble *vec1,GLdouble *vec2,GLdouble *vec3,GLdouble *vec4,GLdouble *normal)
{
  normal[0] = (vec1[1]-vec2[1])*(vec1[2]+vec2[2]) + 
	      (vec2[1]-vec3[1])*(vec2[2]+vec3[2]) + 
	      (vec3[1]-vec4[1])*(vec3[2]+vec4[2]) +
	      (vec4[1]-vec1[1])*(vec4[2]+vec1[2]);
  normal[1] = (vec1[2]-vec2[2])*(vec1[0]+vec2[0]) + 
	      (vec2[2]-vec3[2])*(vec2[0]+vec3[0]) + 
	      (vec3[2]-vec4[2])*(vec3[0]+vec4[0]) +
	      (vec4[2]-vec1[2])*(vec4[0]+vec1[0]);
  normal[2] = (vec1[0]-vec2[0])*(vec1[1]+vec2[1]) + 
	      (vec2[0]-vec3[0])*(vec2[1]+vec3[1]) + 
	      (vec3[0]-vec4[0])*(vec3[1]+vec4[1]) +
	      (vec4[0]-vec1[0])*(vec4[1]+vec1[1]);

  normalise(normal);

}

void Board::paralelo(GLdouble dimx, GLdouble dimy, GLdouble dimz){
	GLdouble dx=dimx/2, dy=dimy/2, dz=dimz/2;
	
	GLdouble v1[3] = {dx,-dy,dz};
	GLdouble v2[3] = {dx,-dy,-dz};
	GLdouble v3[3] = {dx,dy,dz};
	GLdouble v4[3] = {dx,dy,-dz};
	GLdouble v5[3] = {-dx,-dy,dz};
	GLdouble v6[3] = {-dx,dy,dz};
	GLdouble v7[3] = {-dx,dy,-dz};
	GLdouble v8[3] = {-dx,-dy,-dz};
	GLdouble normal[VLENGTH];

	//Face frente - 0
	newellSquare(v1,v3,v6,v5,normal);
	glBegin(GL_POLYGON);
	    glNormal3dv(normal);
		glVertex3dv(v1);
		glVertex3dv(v3);
		glVertex3dv(v6);
		glVertex3dv(v5);
	glEnd();

	// face anterior - 1
	newellSquare(v8,v7,v4,v2,normal);
	glBegin(GL_POLYGON);
	    glNormal3dv(normal);
		glVertex3dv(v8);
		glVertex3dv(v7);
		glVertex3dv(v4);
		glVertex3dv(v2);
	glEnd();

	// face lateral - 2
	newellSquare(v2,v4,v3,v1,normal);
	glBegin(GL_POLYGON);
 	    glNormal3dv(normal);
		glVertex3dv(v2);
		glVertex3dv(v4);
		glVertex3dv(v3);
		glVertex3dv(v1);
	glEnd();

	newellSquare(v5,v6,v7,v8,normal);
	glBegin(GL_POLYGON);
	    glNormal3dv(normal);
		glVertex3dv(v5);
		glVertex3dv(v6);
		glVertex3dv(v7);
		glVertex3dv(v8);
	glEnd();

	// base
	newellSquare(v1,v5,v8,v2,normal);
	glBegin(GL_POLYGON);
	    glNormal3dv(normal);
		glVertex3dv(v1);
		glVertex3dv(v5);
		glVertex3dv(v8);
		glVertex3dv(v2);
	glEnd();

	// topo 
	newellSquare(v3,v4,v7,v6,normal);
	glBegin(GL_POLYGON);
	   glNormal3dv(normal);
		glVertex3dv(v3);
		glVertex3dv(v4);
		glVertex3dv(v7);
		glVertex3dv(v6);
	glEnd();

}

void Board::drawBoard(GLenum mode){

	int x = 0.0;
	int z = 0.0;
	int color;

	glEnable(GL_COLOR_MATERIAL);
	
	for(int i = 0; i < this->dimension; i++){
		if( i%8 == 0){
			z+= 2.0;
			x= 0.0;	
			color++;
		}
		color %= 2;
		
		if(color == 0)
			glColor3f(0.0,0.0,255.0);
		else
			glColor3f(255.0,255.0,0.0);

		glPushMatrix();
		glTranslated(x,0,z);

		if (mode == GL_SELECT){
			glLoadName (i+1);
		}

		paralelo(2.0,1.0,2.0);

		glPopMatrix();
		x += 2.0;
		color++;

	}

		glColor3f(0.0,0.0,255.0);
		glDisable(GL_COLOR_MATERIAL);
}


void Board::hitZone(GLenum mode, int x, int z){

	glEnable(GL_COLOR_MATERIAL);

	for(int j = -2; j < 3; j++){

		for(int i = -2; i < 3; i++){
		
			int xt = x - i;
			int zt = z + j;


			if(j == -2 || j == 2 || i == -2 || i == 2)
				glColor3f(128.0,128.0,0.0);
			else
				glColor3f(0.0,128.0,0.0);

			if(zt == z && xt == x)
				continue;
			else if(zt > 0 && zt <= 8 && xt >= 0 && xt < 8){

				if (mode == GL_SELECT){
					glLoadName ((zt-1)*8+xt+1);
				}

				glPushMatrix();
				glTranslated(2*xt,0,zt*2);
				glBegin(GL_POLYGON);
				glNormal3d(0.0,1.0,0.0);
					glVertex3d(-1.0,1.0,1.0);
					glVertex3d(1.0,1.0,1.0);
					glVertex3d(1.0,1.0,-1.0);
					glVertex3d(-1.0,1.0,-1.0);	
				glEnd();
				glPopMatrix();
			}
		}
	}


	glColor3f(0.0,128.0,0.0);
	glDisable(GL_COLOR_MATERIAL);

}