#include "stdafx.h"
#include "tcpServer.h"

bool SERVER::init(void) {
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);
	int nRet;
	// Init WinSock
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet)
	{
		fprintf(stderr, "\nError initializing WinSock\n");
		return false;
	}
	// Check version
	if (wsaData.wVersion != wVersionRequested)
	{
		fprintf(stderr, "\nWinSock version not supported\n");
		return false;
	}
	int socksize = sizeof(struct sockaddr_in);
	memset(&dest, 0, sizeof(dest));    /* zero the struct before filling the fields */
	serv.sin_family = AF_INET;         /* set the type of connection to TCP/IP */
	serv.sin_addr.s_addr = INADDR_ANY; /* set our address to any interface */
	serv.sin_port = htons(PORTNUM);    /* set the server port number */

	ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Listen socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return false;
	}
	/* bind serv information to mysocket */
	iResult = bind(ListenSocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return false;
	}
	/* start listening, allowing a queue of up to 1 pending connection */
	listen(ListenSocket, 1);
	printf("Init ok\n");
	return true;
}

void SERVER::onData(gotdata _data) {
	hasdata = _data;
};

bool SERVER::loop() {
	if (serverConnected()) {
		int len = receiveMessage(msg, sizeof(msg));
		if (len > 0) {		//	Received data
			msg[len] = 0;
			if (hasdata) hasdata(msg, len);
		}
		else if (len == 0) {
			printf("Closed\n");
			mySocket = INVALID_SOCKET;
		}
		return true;
	};
};

bool SERVER::serverConnected(void) {
	if (mySocket != INVALID_SOCKET) return true;
	mySocket = accept(ListenSocket, NULL, NULL);
	if (mySocket != INVALID_SOCKET) {
		printf("Connected\n");
		return true;
	}
	return false;
}

int SERVER::receiveMessage(char * msg, int len) {
	return recv(mySocket, msg, len, 0);
}

int SERVER::sendMessage(char * msg, int len) {
	return send(mySocket, msg, len, 0);
}

void SERVER::close() {
	printf("Closed\n");
	mySocket = INVALID_SOCKET;
}
