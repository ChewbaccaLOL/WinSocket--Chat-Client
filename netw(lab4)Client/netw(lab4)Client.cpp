#include "pch.h"
#include "Client.h"


int main(int argc, char* argv[]) {
	
	Client myClient("192.168.1.106", 1111);

	if (!myClient.Connecnt())
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	Sleep(20);

	
	std::string msg1;
	while (true) {
		std::getline(std::cin, msg1);
		if (!myClient.SendString(msg1))
			break;
		Sleep(10);
	}

	return 0;
}