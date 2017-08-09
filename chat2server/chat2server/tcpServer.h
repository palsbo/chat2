#pragma once
#include <winsock.h>

#define DEFAULT_BUFLEN 512
#define PORTNUM 6881

typedef void(*gotdata) (char * msg, int len);

class SERVER {
private:
	gotdata hasdata;
	SOCKET mySocket = INVALID_SOCKET;
	SOCKET ListenSocket = INVALID_SOCKET;
	struct sockaddr_in dest; /* socket info about the machine connecting to us */
	struct sockaddr_in serv; /* socket info about our server */
	int iResult = 0;
public:
	char msg[DEFAULT_BUFLEN];
	void onData(gotdata _data);
	bool init(void);
	bool serverConnected();
	int receiveMessage(char * msg, int len);
	int sendMessage(char * msg, int len);
	bool loop();
	void close();
};
