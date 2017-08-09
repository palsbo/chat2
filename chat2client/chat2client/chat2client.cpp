// chat2client.cpp : Defines the entry point for the console application.
//	https://cboard.cprogramming.com/c-programming/121979-simple-hello-world-server-client.html
//
#include "stdafx.h"
#include <windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "tcpClient.h"
#include "kbd.h"

using namespace std;
#pragma comment (lib, "Ws2_32.lib")

CLIENT client;


BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_C_EVENT:
		printf("Ctrl-C event\n\n");
		Beep(750, 200);
		client.close();
		return(FALSE);
	case CTRL_CLOSE_EVENT:	//	close console
		printf("Ctrl-Close event\n\n");
		Beep(600, 200);
		client.close();
		return(FALSE);
	case CTRL_BREAK_EVENT:
		printf("Ctrl-Break event\n\n");
		Beep(900, 200);
		client.close();
		return FALSE;
	case CTRL_LOGOFF_EVENT:
		printf("Ctrl-Logoff event\n\n");
		Beep(1000, 200);
		client.close();
		return FALSE;
	case CTRL_SHUTDOWN_EVENT:
		printf("Ctrl-Shutdown event\n\n");
		Beep(750, 500);
		client.close();
		return FALSE;
	default:
		return FALSE;
	}
}

int main()
{
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{ }
	client.init();
	kbd.onInput([](char * line, int len) {
		if (len == 0) return;
		int myResult = client.sendMessage(line, len);
		printf("\nBytes Sent: %d - %s\n", len, line);
	});
	while (kbd.loop()) {
		if (client.clientConnected()) { 
			int len = client.receiveMessage(client.msg, sizeof(client.msg));
			if (len > 0) {
				printf("Bytes received: %d - Msg: \'%s\'\n", len, client.msg);
			}
		}
	}
	client.close();
}
