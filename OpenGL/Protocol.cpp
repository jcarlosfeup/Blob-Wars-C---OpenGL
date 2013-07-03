#include "Protocol.h"


void Protocol::initConnection(){

	this->connect = new Socket();

	connect->socketConnect();

	update = false;
}


void Protocol::sendData(string Data){

	char * data = (char*) Data.c_str();

	this->connect->envia(data, strlen(data));		
}


string Protocol::receiveData(){

	char ans[this->ans_size];
	this->connect->recebe(ans);

	string answer = (string) ans;

	return answer;
}



void Protocol::parseAnswer(string answer){

	stringstream ss;
	int first = 0, second = 0, indez;

	for(unsigned int i = 0; i < answer.size(); i++){
		if(answer[i] >= 0x30 && answer[i] <= 0x39){ 

			ss << answer[i];
			ss >> indez;
			ss.clear();
			this->array[first][second] = indez;
		
		}
		else if(answer[i] == 0x5D){
			first++;
			second = 0;	
		}
		else if(answer[i] == 0x2C && answer[i-1] != 0x5D)
			second++;
		else
			continue;
	}

}

string Protocol::prepareString(int board[8][8]){

	 string final = "[";
        for(int i = 0 ; i < 8 ; i++){
                final += "[";
                for(int k = 0 ; k < 8 ; k++){
 
                        string element;
                        stringstream out;
                        out << board[i][k];
                        element = out.str();
                        if(k < 7)
                                final += element.append(",");
                        else
                                final += element;
                }

                if(i < 7)
                        final+= "],";
                else
                        final+= "]";
        }
        final+= "]";
 
        return final;
}

string Protocol::sendInf(int type,int player, int xi, int yi, int xf, int yf){

	string data;
	stringstream ss;
	string board;

	switch(type){

		case 1:

			data += "singleMov(";

			ss << xi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << xf;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yf;
			data += ss.str();
			data += ",";

			ss.str("");

			board = prepareString(array);

			data += board;

			data += ").\n";
			break;

		case 2:

			data += "combMov(";

			ss << xi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << xf;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yf;
			data += ss.str();
			data += ",";

			board = prepareString(array);

			data += board;

			data += ").\n";
			break;

		case 3:

			data += "changePec(";

			ss << xf;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yf;
			data += ss.str();
			data += ",";

			board = prepareString(array);

			data += board;

			data += ").\n";
			break;

		case 4:

			data += "validMov(";

			ss << xi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << xf;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yf;
			data += ss.str();
			data += ",";

			ss.str("");

			board = prepareString(array);

			data += board;

			data += ").\n";
			break;

		case 5:

			data += "dist(";

			ss << xi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yi;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << xf;
			data += ss.str();
			data += ",";

			ss.str("");

			ss << yf;
			data += ss.str();

			ss.str("");

			data += ").\n";
			break;

		case 6:

			data += "afterPass(";

			board = prepareString(array);
			data += board;

			data += ",";

			ss << player;
			data += ss.str();
			
			ss.str("");

			data += ").\n";
			break;

		case 7:

			data += "aI(";

			board = prepareString(array);
			data += board;

			data += ",";

			ss << player;
			data += ss.str();
			
			ss.str("");

			data += ").\n";
			break;
	}

	return data;
}