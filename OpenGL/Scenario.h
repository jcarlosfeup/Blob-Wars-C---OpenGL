#ifndef SCENARIO_H_
#define SCENARIO_H_


#include <GL/glui.h>
#include <math.h>
#include <vector>

using namespace std;

class Scenario{

public:
	
	Scenario();
	void buildScenario(int num_cena);
	void cena1();
	void cena2();
	void cena3();
};

#endif