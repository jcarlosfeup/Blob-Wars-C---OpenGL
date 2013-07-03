// aulas.cpp : Defines the entry point for the console application.
//

#include <GL/glui.h>

#include <math.h>
#include "RGBpixmap.h"
#include "Board.h"
#include "Piece.h"
#include "Protocol.h"
#include "Socket.h"
#include "Move.h"
#include "Score.h"
#include "Scenario.h"
#include <windows.h>

#define getCurrentTime GetTickCount

#define DIMX 600
#define DIMY 600
#define INITIALPOS_X 100
#define INITIALPOS_Y 100

#define BUFSIZE 512

float xy_aspect;		// aspect ratio da area de visualizacao
int window_w=DIMX;
int window_h=DIMY;

// picking
GLuint selectBuf[BUFSIZE];

float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };

// variaveis globais
int main_window;
GLUI *glui, *glui2, *glui3;

// declaracoes para as paredes
float mat1_shininess[] = {128.0}; 
float mat1_specular[] = {0.3, 0.3, 0.3, 1.0};	/* specular reflection. */
float mat1_diffuse[] =  {0.7, 0.7, 0.7, 1.0};	/* diffuse reflection. */
float mat1_ambient[] =  {0.7, 0.7, 0.7, 1.0};	/* ambient reflection. */

float mat2_shininess[] = {1.0}; 
float mat2_specular[] = {0.4, 0.4, 0.4, 1.0}; /* specular reflection. */
float mat2_diffuse[] = {0.3, 0.30, 0.30, 1.0}; /* diffuse reflection. */

//Variáveis para as luzes
float light0_position[]  = {8.0, 5.0, 8.0, 1.0}; 
float light0_ambient[] =   {7.0, 7.0, 7.0, 1.0}; 
float light0_diffuse[] =   {7.0, 7.0, 7.0, 1.0};
float light0_specular[] =  {2.0, 2.0, 2.0, 1.0};
float light0_kc = 1.0;
float light0_kl = 0.0;
float light0_kq = 0.0;
double light0x = 8.0;
double light0y = 10.0;
double light0z = 10.0;

// fonte (global) de luz ambiente 
float light_ambient[] = {0.6, 0.6, 0.6, 1.0}; /* Set the background ambient lighting. */

RGBpixmap pix[2];
RGBpixmap pixmap;
GLUquadric* glQ;

//player
int player = 1;
int pont1 = 0,pont2 = 0;

//Movement
int coord[2];
bool can = false;

//Views Selector
int view;
int angle;

//animations
unsigned int mili_secs = 10;
double delta, deltAngle = 0;

//tabuleiro
Board* tabuleiro;

//Declarations of values pieces
vector<Piece*> piece;
int posPiece[8][8];
int selectPiec;

//Conection
Protocol * protoc;
Socket * sock;

//Repeat
vector<Move * > movie;
int indic = 0;
float inc = 0;
bool replaySet = false;

//IA
bool ia = false;

//Score
Score* pontuacao_jog1 = new Score();
Score* pontuacao_jog2 = new Score();
int time = 0, deltaTime = 0;

//Scene
Scenario* cenas = new Scenario();
int cenario;
int ID_CENA = 1;

//gameMode
int gameMode = 1;

enum stat_maq {
	pieces, cells, moves
};

stat_maq step = pieces;

void myInitTransforms()
{
	delta = 1;
	
}


void myUpdateTransforms(int dummy)
{
	if (view == 0 && deltAngle > angle)
		deltAngle -= delta;
	else if(view == 1 && deltAngle < angle)
		deltAngle += delta;

	if(replaySet)
		inc += 0.08;
	
	if(inc >= 2.0 && replaySet && indic < movie.size() - 1){
		inc = 0;
		indic++;
	}

	
	deltaTime++;
	if(deltaTime == 100){
		time++;
		deltaTime = 0;
	}

	if(time == 60)
		time = 0;

	glutTimerFunc(mili_secs, myUpdateTransforms, 0);
}

void getUpdate(string board,int x, int z){

	protoc->parseAnswer(board);

	Move *cartoon = new Move(coord[0],coord[1],x,z);

	for(int i = 0; i < 8; i++){
		for(int o = 0; o < 8; o++){

			posPiece[i][o] = protoc->array[i][o];
			cartoon->board[i][o] = protoc->array[i][o];

		}
	}

	movie.push_back(cartoon);
}

void actPieces(){

	piece.clear();
	pont1 = 0;
	pont2 = 0;

	for(unsigned int i = 0; i < 8; i++){
		for(unsigned int o = 0; o < 8; o++){

			if(posPiece[i][o] != 0){
				Piece* pec = new Piece(o+1,i+1,posPiece[i][o]);
				piece.push_back(pec);
				if(posPiece[i][o] == 1)
					pont1++;
				else
					pont2++;
			}
			else
				continue;
		}
	}
}

void replay(){

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			posPiece[i][j] = movie[indic]->board[i][j];
		}
	}
	
	actPieces();
}

void iaMove(){
	
		string inf = protoc->sendInf(7,player,0,0,0,0);

		protoc->sendData(inf);
				
		string board = protoc->receiveData();

		protoc->parseAnswer(board);

		getUpdate(board,0,0);

		actPieces();

		if(player == 1)
			player = 2;
		else
			player = 1;

		ia = false;
}

void connectSock(int x, int z){

	string inf, board;
	stringstream ss;
	float dist;

	inf = protoc->sendInf(4,0,coord[0],coord[1],x,z);

	protoc->sendData(inf);

	board = protoc->receiveData();

	if(board[0] == '1'){
				
		inf = protoc->sendInf(5,0,coord[0],coord[1],x,z);
	
		protoc->sendData(inf);

		board = protoc->receiveData();

		ss << board;
	
		ss >> dist;

		if(dist < 2.0){

			inf = protoc->sendInf(1,0,coord[0],coord[1],x,z);

			protoc->sendData(inf);

			board = protoc->receiveData();

			protoc->parseAnswer(board);

			inf = protoc->sendInf(3,0,0,0,x,z);

			protoc->sendData(inf);
			
			board = protoc->receiveData();

			protoc->parseAnswer(board);

			getUpdate(board,x,z);

			actPieces();

			if(player == 1)
				player = 2;
			else if(player == 2)
				player = 1;
			
			if(gameMode == 2)
				ia = true;
	
		}else if(dist >= 2.0 && dist < 3.0){
		
			inf = protoc->sendInf(2,0,coord[0],coord[1],x,z);

			protoc->sendData(inf);

			board = protoc->receiveData();

			protoc->parseAnswer(board);

			inf = protoc->sendInf(3,0,0,0,x,z);

			protoc->sendData(inf);
			
			board = protoc->receiveData();

			protoc->parseAnswer(board);

			getUpdate(board,x,z);

			actPieces();

			if(player == 1)
				player = 2;
			else if(player == 2)
				player = 1;

			if(gameMode == 2)
				ia = true;
	

		}
	}
}

void showWinner(int winner){

	int dimX = 35;
	int dimY = 40;
	int dimZ = 5;

	glEnable(GL_TEXTURE_2D);
	
	if(winner == 1)
		glBindTexture(GL_TEXTURE_2D,27);
	else
		glBindTexture(GL_TEXTURE_2D,28);
	
	glPushMatrix();
	glTranslated(7,-30,0);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,1.0);glVertex3d(-dimX,dimY,-dimZ);
		glTexCoord2f(0.0,0.0);glVertex3d(-dimX,0.0,-dimZ);
		glTexCoord2f(1.0,0.0);glVertex3d(dimX,0.0,-dimZ);
		glTexCoord2f(1.0,1.0);glVertex3d(dimX,dimY,-dimZ);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void drawScene(GLenum mode)
{
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 200.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslated(-8.0,0.0,-48.0);
	glRotated(45.0, 1.0,0.0,0.0 );
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] ); 
	glMultMatrixf( view_rotate );

	glTranslatef(8.0,0.0,8.0);
	glRotated(deltAngle,0.0,1.0,0.0);
	glTranslatef(-8.0,0.0,-8.0);
	
	if (mode == GL_SELECT)
		glPushName (0);

	if(pont1 == 0 || pont2 == 0){
		if(pont1 > pont2)
			showWinner(2);
		else
			showWinner(2);
	}
	else{

		for(unsigned int i = 0; i < piece.size();i++){
			piece[i]->buildPiece(mode,glQ,i+65);
		}
		
		
		if(can)
			tabuleiro->hitZone(mode,coord[0]-1,coord[1]);
		tabuleiro->drawBoard(mode);

		glPushMatrix();
		glTranslated(7.0,0.0,9.0);
		cenas->buildScenario(ID_CENA);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-7.0,0.0,17.0);
		glRotated(-90,1.0,0.0,0.0);
		pontuacao_jog1->buildBoardScore();
		glPopMatrix();

		glPushMatrix();
		glTranslated(21.0,0.0,1.5);
		glRotated(180,0.0,1.0,0.0);
		glRotated(-90,1.0,0.0,0.0);
		pontuacao_jog2->buildBoardScore();
		glPopMatrix();

		pontuacao_jog1->updateScore(pont1);
		pontuacao_jog2->updateScore(pont2);
		pontuacao_jog1->updateTime(time);
		pontuacao_jog2->updateTime(time);

		glDisable(GL_COLOR_MATERIAL);
	}

	glPopName();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
    glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	// Actualizacao da posicao da fonte de luz
	light0_position[0] = light0x;	
	light0_position[1] = light0y;	
	light0_position[2] = light0z;
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// Definicao de material a usar daqui em diante (valores declarados acima)
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat1_ambient);
	
	if(replaySet)
		replay();

	if(ia){
		iaMove();
		ia = false;
	}

	if(indic == movie.size() - 1){
		replaySet = false;
		indic = 0;
		inc = 0;
		
	}

	drawScene(GL_RENDER);

	glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,500,0,500,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(47.0, 47.0, 79.0);		
	glRasterPos3f(5,480,0);
			_glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Player ");
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, char(player+48));
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
   
	glFlush();
}

// ACÇÃO DO PICKING
void pickingAction(GLuint answer) {

	int x,z;
		
	if(answer > 64 && step == pieces)
	{	
		cout << "player " << player << endl;

		selectPiec = answer-65;
		
		x = piece[selectPiec]->getX()/2 + 1;
		z = piece[selectPiec]->getZ()/2;

		if(posPiece[z-1][x-1] == player){
			
			cout << "Piece coords: ";
			cout << z << " " << x << endl;

			coord[0] = x;
			coord[1] = z;
			can = true;
			step = cells;
		}
	}
	else if(answer <= 64 && step == cells){
		
		x = answer % 8;
		z = answer / 8;

		if(x == 0) 
			x = 8;
		else
			z += 1;

		cout << "Cell: " << x << " " << z << endl;

		connectSock(x, z);

		can = false;
		step = pieces;
		
		time = 0;
	}
	else{
		printf("%d\n", answer);
		can = false;
		step = pieces;
	}
}

// processa os hits no picking
void processHits (GLint hits, GLuint buffer[]) {
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *answer=NULL;
	GLuint nn;

	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			answer = ptr;
			nn=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// existe uma resposta
	if (answer!=NULL) 
		pickingAction(*answer);
}

struct g_mouseState{
	bool leftButton;
	bool rightButton;
	bool middleButton;
	int x;
	int y;
} MouseState;

/* Mouse handling */
void processMouse(int button, int state, int x, int y) {
    GLint hits;
	GLint viewport[4];

	// update our button state
	if(button == GLUT_LEFT_BUTTON) {
		if(state == GLUT_DOWN)
			MouseState.leftButton = true;
		else
			MouseState.leftButton = false;
	}
	if(button == GLUT_RIGHT_BUTTON) {
		if(state == GLUT_DOWN)
			MouseState.rightButton = true;
		else
			MouseState.rightButton = false;
	}
	if(button == GLUT_MIDDLE_BUTTON) {
		if(state == GLUT_DOWN)
			MouseState.middleButton = true;
		else
			MouseState.middleButton = false;
	}

	// update our position so we know a delta when the mouse is moved
	MouseState.x = x;
	MouseState.y = y;
		
	if (MouseState.leftButton && !MouseState.rightButton && !MouseState.middleButton) {
		/* obrigatorio para o picking */
		// obter o viewport actual
		glGetIntegerv(GL_VIEWPORT, viewport);

		glSelectBuffer (BUFSIZE, selectBuf);
		glRenderMode (GL_SELECT);

		// inicia processo de picking
		glInitNames();
		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();

		//  cria uma região de 5x5 pixels em torno do click do rato para o processo de picking
		glLoadIdentity ();
		gluPickMatrix ((GLdouble) x, (GLdouble) (window_h - y), 1.0, 1.0, viewport);
		
		drawScene(GL_SELECT);
		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();

		hits = glRenderMode(GL_RENDER);
		processHits(hits, selectBuf);
	}
}

void processMouseMoved(int x, int y)
{	

}

void processPassiveMouseMoved(int x, int y)
{
	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	window_w = w;	//variaveis globais; window_h e' usado em processMouse()
	window_h = h;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	// ver, nos manuais, a funcao GLUI_Master.auto_set_viewport()

	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:// tecla de escape termina o programa
		  protoc->closeConnection();
		  exit(0);
         break;
	  case 113:
		  if(indic < movie.size() - 1)
			  indic++;
		  else
			  cout << "Não dá mais" << endl;
		  break;
   }
}

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  


  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/

//  glui->sync_live();

}

void inicializacao()
{
	float ambient[] = {0.5, 0.5, 0.5, 1.0};
	float diffuse0[] = {1.0, 1.0, 1.0, 1.0}; 
	float diffuse1[] = {0.0, 1.0, 0.0, 1.0}; 
	float position0[] = {1.0, 0.0, 1.0, 0.0}; 
	float position1[] = {50.0, 0.0, 0.0, 0.0}; /* To our right. */
	float lmodel_ambient[] = {0.0, 0.0, 0.0, 1.0}; /* Set the background ambient lighting. */

	glFrontFace(GL_CCW); /* Front faces defined using a counterclockwise rotation. */
	glDepthFunc(GL_LEQUAL); /* Por defeito e GL_LESS */
	glEnable(GL_DEPTH_TEST); /* Use a depth (z) buffer to draw only visible objects. */
	//glEnable(GL_CULL_FACE); /* Use back face culling to improve speed. */
	//glCullFace(GL_BACK); /* Cull only back faces. */
	
	// Define que modelo de iluminacao utilizar; consultar o manual de referencia
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);  // define luz ambiente
	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);  // define luz ambiente
	
	// declaracoes para a fonte luz GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

	// Permitir calculos de iluminacao
	glEnable(GL_LIGHTING);
	// "Acender" a fonte de luz GL_LIGHT0
	glEnable(GL_LIGHT0);

	//glEnable(GL_TEXTURE_2D);				//
	pix[0].makeCheckBoard();				// cria texturas
	pix[0].setTexture(2001);
	pix[1].readBMPFile((char*)"wood2.bmp");	//pix[1].readBMPFile("textura.bmp");
	pix[1].setTexture(2002);

	pixmap.readBMPFile("textures/0.bmp");
	pixmap.setTexture(0);

	pixmap.readBMPFile("textures/1.bmp");
	pixmap.setTexture(1);

	pixmap.readBMPFile("textures/2.bmp");
	pixmap.setTexture(2);

	pixmap.readBMPFile("textures/3.bmp");
	pixmap.setTexture(3);

	pixmap.readBMPFile("textures/4.bmp");
	pixmap.setTexture(4);

	pixmap.readBMPFile("textures/5.bmp");
	pixmap.setTexture(5);

	pixmap.readBMPFile("textures/6.bmp");
	pixmap.setTexture(6);

	pixmap.readBMPFile("textures/7.bmp");
	pixmap.setTexture(7);

	pixmap.readBMPFile("textures/8.bmp");
	pixmap.setTexture(8);

	pixmap.readBMPFile("textures/9.bmp");
	pixmap.setTexture(9);

	pixmap.readBMPFile("textures/score.bmp");
	pixmap.setTexture(10);

	pixmap.readBMPFile("textures/time.bmp");
	pixmap.setTexture(11);

	pixmap.readBMPFile("textures/room.bmp");
	pixmap.setTexture(12);

	pixmap.readBMPFile("textures/room2.bmp");
	pixmap.setTexture(13);

	pixmap.readBMPFile("textures/tapete.bmp");
	pixmap.setTexture(14);

	pixmap.readBMPFile("textures/tapete2.bmp");
	pixmap.setTexture(15);

	pixmap.readBMPFile("textures/sea.bmp");
	pixmap.setTexture(16);

	pixmap.readBMPFile("textures/sand.bmp");
	pixmap.setTexture(17);

	pixmap.readBMPFile("textures/forest.bmp");
	pixmap.setTexture(18);

	pixmap.readBMPFile("textures/towel.bmp");
	pixmap.setTexture(19);

	pixmap.readBMPFile("textures/metal.bmp");
	pixmap.setTexture(20);

	pixmap.readBMPFile("textures/wall.bmp");
	pixmap.setTexture(21);

	pixmap.readBMPFile("textures/tapete3.bmp");
	pixmap.setTexture(22);

	pixmap.readBMPFile("textures/tapete4.bmp");
	pixmap.setTexture(23);

	pixmap.readBMPFile("textures/game.bmp");
	pixmap.setTexture(24);

	pixmap.readBMPFile("textures/jogvscom.bmp");
	pixmap.setTexture(25);

	pixmap.readBMPFile("textures/jogvsjog.bmp");
	pixmap.setTexture(26);

	pixmap.readBMPFile("textures/wp1.bmp");
	pixmap.setTexture(27);

	pixmap.readBMPFile("textures/wp2.bmp");
	pixmap.setTexture(28);

	// por defeito a cor e de fundo e o preto
	//glClearColor(1.0,1.0,1.0,1.0);

	/* Set the light properties */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	/* Which shade model to use: GL_FLAT / GL_SMOOTH. */
	glShadeModel(GL_SMOOTH);


	glQ = gluNewQuadric();
	gluQuadricOrientation(glQ, GLU_OUTSIDE);

	//Inicializações
	tabuleiro = new Board(8);
	protoc = new Protocol();
	protoc->initConnection();


	protoc->sendData("initialBoard.\n");
	string board = protoc->receiveData();
	getUpdate(board,0,0);
	actPieces();

	myInitTransforms();
}

void setView(int dummy){
	
	switch(view){
	case 0:
		angle = 0;
		break;
	case 1: 
		angle = 180;
		break;
	}
	
}

void setMovie(int value)
{
	if(!replaySet){	
		replaySet = true;
	}
}

void afterPass(int value)
{
	int sendP = 0;

	if(player == 1)
		sendP = 2;
	else
		sendP = 1;
	
	string inf = protoc->sendInf(6,sendP,0,0,0,0);

	protoc->sendData(inf);
			
	string board = protoc->receiveData();

	protoc->parseAnswer(board);

	getUpdate(board,0,0);

	actPieces();
}

void listbox_callback(int value){

	switch(cenario){

	case 1:		
		ID_CENA = 1;
		break;
	case 2:
		ID_CENA = 2;
		break;
	case 3:
		ID_CENA = 3;
		break;
	}
	
	return;
}

void undo(int value){

	unsigned int size = movie.size();
	int und = size - 4;

	if(und < 0)
		und = 0;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			posPiece[i][j] = movie[und]->board[i][j];
			protoc->array[i][j] = movie[und]->board[i][j];

		}
	}

	vector<Move*>::iterator it = movie.end();
	
	actPieces();
}


int main(int argc, char* argv[])
{
	cout << "BLOB WARS" << endl << "1. Human vs Human" << endl << "2. Human vs IA" << endl;
	cout << "GAME MODE: ";
	cin >> gameMode;

   glutTimerFunc(mili_secs, myUpdateTransforms, 0);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (DIMX, DIMY);
   glutInitWindowPosition (INITIALPOS_X, INITIALPOS_Y);
   main_window = glutCreateWindow (argv[0]);
 
   glutDisplayFunc(display);
   GLUI_Master.set_glutReshapeFunc(reshape);
   GLUI_Master.set_glutKeyboardFunc (keyboard);
   GLUI_Master.set_glutMouseFunc(processMouse);
   glutMotionFunc(processMouseMoved);
   glutPassiveMotionFunc(processPassiveMouseMoved);   
   GLUI_Master.set_glutSpecialFunc( NULL );


	/*** Create the bottom subwindow ***/
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
														/*	GLUI_SUBWINDOW_RIGHT
															GLUI_SUBWINDOW_LEFT
															GLUI_SUBWINDOW_TOP
															GLUI_SUBWINDOW_BOTTOM */
	glui2->set_main_gfx_window( main_window );

	glui2->add_statictext("Views");
	GLUI_RadioGroup *views = 
		glui2->add_radiogroup(&view,-1,setView);
	
	GLUI_RadioButton *viewsOpt = 
		glui2->add_radiobutton_to_group(views,"Player1");
	viewsOpt = 
		glui2->add_radiobutton_to_group(views,"Player2");

	
	glui3 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM);
	glui3->set_main_gfx_window( main_window );

	GLUI_Translation *trans_z = 
	glui3->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );

	glui3->add_column( false );
	GLUI_Translation *trans_xy =
	glui3->add_translation("Navegar", GLUI_TRANSLATION_XY, obj_pos);
	trans_xy->set_speed(.02);

	glui2->add_column( false );	
	GLUI_Listbox *cenario_listbox = glui2->add_listbox("Cenario",&cenario,cenario,listbox_callback);
	//  Add the items to the listbox
	cenario_listbox->add_item (1,"Room");
	cenario_listbox->add_item (2,"Nature");
	cenario_listbox->add_item (3,"Industrial");

	glui2->add_column(false);
	GLUI_Button *movie_button = glui2->add_button("Movie",1,setMovie);

	glui2->add_column(false);
	GLUI_Button *pass_button = glui2->add_button("Skip",2,afterPass);

	glui2->add_column(false);
	GLUI_Button *undo_button = glui2->add_button("Undo",3,undo);

	/* We register the idle callback with GLUI, not with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
   
	inicializacao();

	glutMainLoop();

	return 0;
}
