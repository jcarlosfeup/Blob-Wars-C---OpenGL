#ifndef PROTOCOL_H_
#define PROTOCOL_H_


#include <string>
#include <sstream>
#include "Socket.h"

using namespace std;

class Protocol{

private: 

	Socket *connect;
	static const int ans_size  = 256;
	bool update;

public:

	int array[8][8];
	bool needUpdate(){return update;}
	void setUpdate(bool value){this->update = value;}
	void initConnection();
	void sendData(string data);
	string receiveData();
	void parseAnswer(string answer);
	string prepareString(int board[8][8]);
	string sendInf(int type,int player, int xi, int yi, int xf, int yf);
	void closeConnection(){this->connect->quit();}



};




#endif