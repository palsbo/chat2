#include "stdafx.h"
#include "tcpClient.h"

bool CLIENT::init() {
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&dest, 0, sizeof(dest));                /* zero the struct */
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number */
	dest.sin_port = htons(PORTNUM);                /* set destination port number */
	WSADATA wsaData;

	WORD wVersionRequested = MAKEWORD(1, 1);
	int nRet;
	// Init WinSock
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet)
	{
		printf("\nError initializing WinSock\n");
		return false;
	}
	// Check version
	if (wsaData.wVersion != wVersionRequested)
	{
		printf("\nWinSock version not supported\n");
		return false;
	}
	printf("Init ok\n");
	return true;
}

bool CLIENT::clientConnected() {
	if (mySocket != INVALID_SOCKET) return true;
	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mySocket == INVALID_SOCKET) {
		return false;
	}
	iResult = connect(mySocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
	if (iResult == SOCKET_ERROR) {
		closesocket(mySocket);
		mySocket = INVALID_SOCKET;
		return false;
	}
	u_long iMode = 1;
	iResult = ioctlsocket(mySocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(mySocket);
		WSACleanup();
		exit(1);
	}
	return true;
}

int CLIENT::receiveMessage(char * buf, int len) {
	return recv(mySocket, buf, len, 0);
}

bool CLIENT::sendMessage(char * msg, int len) {
	return send(mySocket, msg, len, 0);
}

bool CLIENT::close() {
	closesocket(mySocket);
	return true;
}
