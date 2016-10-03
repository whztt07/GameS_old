#include "stdafx.h"
#include <winsock2.h>
#include <string>
#include <time.h>


#include "Client.h"
#include "Processing.h"
#include "Account.h"
#include "GameLogic.h"
#include "Global.h"




void Client::Init(GameLogic *game){
	Account::Init();
	Processing::Init(game);
}

unsigned _stdcall Client::ToClient(void * pvoid){
	
	char buff[CLIENT_BUFFER_SIZE];
	
	SOCKET Socket;
	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	u_short port = BEGIN_PORT;
	sockaddr_in local_addr = ((sockaddr_in*)pvoid)[0];
	sockaddr_in client_add = local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);

	

	while (1)
	{
		if (bind(Socket, (sockaddr *)&local_addr, sizeof(local_addr))){
			if (WSAEADDRINUSE == WSAGetLastError())
			{
				port++;
				local_addr.sin_port = htons(port);
			}
			else{
				closesocket(Socket);
				WSACleanup();
				return -1;
			}
		}
		else{
			break;
		}
	}
	
	string ss = "Port|" + to_string(port) + "|";
	sendto(Socket, &ss[0], ss.length(), 0, (sockaddr *)&client_add, sizeof(client_add));
	sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);
	Account acc = Account();
	int my_lastTimeUPD = clock();
	fd_set read_s; // Множество
	timeval time_out; // Таймаут
	int res;
	while (1){
		FD_ZERO(&read_s); // Обнуляем множество
		FD_SET(Socket, &read_s); // Заносим в него наш сокет 
		
		time_out.tv_sec = 0; time_out.tv_usec = 500000; //Таймаут 0.5 секунды.
		if (SOCKET_ERROR == (res = select(0, &read_s, NULL, NULL, &time_out))) return -1;
		
		if ((res != 0) && (FD_ISSET(Socket, &read_s))) // Использую FD_ISSET только для примера! :)
		{

			int bsize = recvfrom(Socket, &buff[0], sizeof(buff)-1, 0, (sockaddr *)&client_addr, &client_addr_size);
			string s;
			if (bsize > -1){
				s = string(buff, bsize);
				s = Processing::Process(s, acc);
			}
			else{
				s = "NULL";
			}
			if (s != "NULL")
			sendto(Socket, &s[0], s.length(), 0, (sockaddr *)&client_addr, sizeof(client_addr));
			if (s == "YouKick|"){
				closesocket(Socket);
				Processing::Leave(acc);
				return -1;
			}
			my_lastTimeUPD = clock();
			
		}
		else{

			if (clock() - my_lastTimeUPD > MAX_WAIT_CLIENT_TIME){
				closesocket(Socket);
				Processing::Leave(acc);
				return -1;
			}
		}
	}

}

const int Client::GetClientCount(){
	return Processing::GetClientCount();
}

