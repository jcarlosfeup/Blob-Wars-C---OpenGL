#ifndef SOCKET_H_
#define SOCKET_H_

#include <winsock2.h>
#include <iostream>
#define IPADDRESS "127.0.0.1"
#define PORT 60070

using namespace std;

class Socket{

private:
		
	SOCKET m_socket;

public:
	
	Socket(){}
	bool socketConnect();
	void envia(char *s, int len);
	void recebe(char *ans);
	void quit();

};

#endif