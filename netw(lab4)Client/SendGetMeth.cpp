#include "pch.h"
#include "Client.h"

bool Client::SendInt(int _int)
{
	int RetnCheck = send(Connection, (char*)&_int, sizeof(int), NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::GetInt(int & _int)
{
	int RetnCheck = recv(Connection, (char*)&_int, sizeof(int), NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::SendPacketType(Packet _packettype)
{
	int RetnCheck = send(Connection, (char*)&_packettype, sizeof(Packet), NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::GetPacketType(Packet & _packettype)
{
	int RetnCheck = recv(Connection, (char*)&_packettype, sizeof(Packet), NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::SendString(std::string & _string) {
	if (!SendPacketType(P_ChatMessage))
		return false;
	_string = "<" + clientname +"> " + _string;
	int bufferlength = _string.size();
	if (!SendInt(bufferlength))
		return false;
	int RetnCheck = send(Connection, _string.c_str(), bufferlength, NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Client::GetString(std::string & _string) {
	int bufferlength;
	if (!GetInt(bufferlength))
		return false;
	char * buffer = new char[bufferlength + 1];
	buffer[bufferlength] = '\0';
	int RetnCheck = recv(Connection, buffer, bufferlength, NULL);
	_string = buffer;
	delete[] buffer;
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

