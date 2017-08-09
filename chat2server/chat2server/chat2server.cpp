// chat2server.cpp : Defines the entry point for the console application.
//
//	https://cboard.cprogramming.com/c-programming/121979-simple-hello-world-server-client.html
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcpServer.h"

#pragma comment (lib, "Ws2_32.lib")

SERVER server;

/*	Alternative main.

int main()
{
	if (!server.init()) return false;
	server.onData([](char * msg, int len) {
		printf("Data: %d %s\n", len, msg);
		server.sendMessage("Thank you", 9);
	});
	for (;;) server.loop();
}
*/

int main() {
	if (!server.init()) return false;
	for (;;) {
		if (server.serverConnected()) {
			int len = server.receiveMessage(server.msg, sizeof(server.msg));
			if (len == 0) server.close();
			if (len > 0) {
				printf("Data: %d %s\n", len, server.msg);
				server.sendMessage("Thank you", 9);
			}
		}
	}
}
