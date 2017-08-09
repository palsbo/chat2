#pragma once
//#include "stdafx.h"
#include <winsock.h>


#define MAXRCVLEN 500
#define DEFAULT_BUFLEN 512
#define PORTNUM 6881

class CLIENT {
private:
	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	int len;
	SOCKET mySocket;
	SOCKET ListenSocket;
	struct sockaddr_in dest;
	int iResult;
public:
	char msg[DEFAULT_BUFLEN];
	bool init();
	bool clientConnected();
	int receiveMessage(char * buf, int len);
	bool sendMessage(char * msg, int len);
	bool close();
};
