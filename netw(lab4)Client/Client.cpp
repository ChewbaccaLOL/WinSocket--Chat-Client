#include "pch.h"
#include "Client.h"
#include <windows.h>

Client::Client(std::string IP, int PORT)
{
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) 
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}


	addr.sin_addr.s_addr = inet_addr(IP.c_str());
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;
	clientptr = this;
}

bool Client::Connecnt()
{
	std::cout << "Enter your nickname ";
	std::getline(std::cin, clientname);
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) {
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//std::cout << "Connected!\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);

	return true;
}

bool Client::ProcessPacket(Packet _packettype)
{
	switch (_packettype) {
	case P_ChatMessage:
	{
		std::string Message;
		if (!GetString(Message))
			return false;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // For use of SetConsoleTextAttribute()

		SetConsoleTextAttribute(console, 14); // set color for the next print
		std::cout << '\r' + Message << std::endl;
		SetConsoleTextAttribute(console, 7); // set color for the next print
		break;
	}
	default:
		std::cout << "Unrecognized packet: " << _packettype << std::endl;
		break;
	}

	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(Connection) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK)
			return true;

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error",MB_OK | MB_ICONERROR);
		return false;

	}
	return true;
}

void Client::ClientThread() 
{
	Packet packettype;
	while (true) {
		if (!clientptr->GetPacketType(packettype))
			break;
		if (!clientptr->ProcessPacket(packettype)) {
			break;
		}
	}
	std::cout << "Lost connection to the server." << std::endl;
	if (clientptr->CloseConnection())
	{
		std::cout << "Socket to the server was closed successfuly." << std::endl;
	}
	else
	{
		std::cout << "Socket was not able to be closed." << std::endl;
	}
}