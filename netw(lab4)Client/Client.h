#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable: 4996)


enum Packet
{
	P_ChatMessage,
	P_Test
};


class Client
{
public:
	Client(std::string IP, int PORT);
	bool Connecnt();
	bool CloseConnection();
	bool SendString(std::string & _string);
private:
	bool ProcessPacket(Packet _packettype);
	static void ClientThread();
	//send
	bool SendInt(int _int);
	bool SendPacketType(Packet _packettype);

	//get
	bool GetInt(int & _int);
	bool GetPacketType(Packet & _packettype);
	bool GetString(std::string & _string);
private:
	SOCKET Connection;
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	std::string clientname;

};

static Client * clientptr;