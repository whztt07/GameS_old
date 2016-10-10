
#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>  
#include <ws2tcpip.h>
#include <windows.h>

#include <string>
#include <iostream>
#include <process.h>

#include "Connection.h"
#include "Client.h"
#include "GameLogic.h"
#include "Global.h"

#pragma comment ( lib, "ws2_32.lib" )



using namespace std;

SOCKET Connection::Socket;

void Connection::Init(GameLogic &game){

	char buff[128];

	WSAStartup(0x202, (WSADATA *)&buff[0]);

	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (Socket == INVALID_SOCKET)
	{
		WSACleanup();
	};

	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(MAIN_PORT);

	if (bind(Socket, (sockaddr *)&local_addr, sizeof(local_addr)))
	{
		closesocket(Socket);
		WSACleanup();
	};

	Client::Init(game);
}

unsigned _stdcall Connection::ConnectMy(void* pvoid){
	
	char buff[128];// Должно приходить только "Connect"
	sockaddr_in client_addr;
	while (1)
	{
		
		int client_addr_size = sizeof(client_addr);
		int bsize = recvfrom(Socket, &buff[0], sizeof(buff)-1, 0, (sockaddr *)&client_addr, &client_addr_size);
		if (bsize == SOCKET_ERROR){
			printf("recvfrom() error: %d\n", WSAGetLastError());
		}
		string s = string(buff, bsize);
		if (s == "Connect"){
			_beginthreadex(NULL, NULL, Client::ToClient, new sockaddr_in(client_addr), NULL, NULL);
		}
	}
	
	return -1;

}


int Connection::GetClientCount(){
	return Client::GetClientCount();
}

void Connection::RunThread(){

	_beginthreadex(NULL, NULL, ConnectMy, NULL, NULL, NULL);

}