#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>

	using namespace std;

class Move{

private:

	int xi,xf,yi,yf;

public:

	int board[8][8];
	Move(int x1,int x2,int y1,int y2);
	~Move(){};


};

#endif