#ifndef SCORE_H_
#define SCORE_H_


#include <GL/glui.h>
#include <math.h>
#include <vector>

using namespace std;

class Score{

private:
	
	int score;
	int time;
	
public:
	GLUquadric* glQ;

	Score();
	void updateScore(int new_score);
	void updateTime(int time){this->time = time;}
	void buildBoardScore();
	void parserScore(vector<int> &pont);
	void parserTime(vector<int> &time);

};

#endif