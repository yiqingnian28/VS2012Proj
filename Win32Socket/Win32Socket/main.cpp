
#pragma comment(lib,"ws2_32.lib")

#include<WinSock2.h>

#include<iostream>

using namespace std;

#define IP_ADDRESS "172.16.1.239"

int main(int argc, char** argv){
	WSADATA  Ws;
    SOCKET CientSocket;
	struct sockaddr_in ServerAddr;
	int Ret = 0;
	int AddrLen = 0;
	HANDLE hThread = NULL;
	char SendBuffer[MAX_PATH];

	cout << "argc = " << argc << ", argv = " << argv[0] << endl;

	//Init Windows Socket
	if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
	{
	cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
	return -1;
	}

	//Create Socket
	CientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ( CientSocket == INVALID_SOCKET )
		 {
	cout<<"Create Socket Failed::"<<GetLastError()<<endl;
	return -1;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	
	unsigned short port = 6666;
	if(argc == 2){
		port = (unsigned short)strtoul(argv[1], NULL, 10);
	}
	cout << "trying port " << port << endl;
	ServerAddr.sin_port = htons(port);
	
	memset(ServerAddr.sin_zero, 0x00, 8);

	Ret = connect(CientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
	if ( Ret == SOCKET_ERROR )
	{
		cout<<"Connect Error::"<<GetLastError()<<endl;
		return -1;
	}
	else
	{
		cout<<"连接成功!"<<endl;
	}

	while ( true )
	{
		cin.getline(SendBuffer, sizeof(SendBuffer));
		Ret = send(CientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
		if ( Ret == SOCKET_ERROR )
		{
			cout<<"Send Info Error::"<<GetLastError()<<endl;
			break;
		}
	}

	closesocket(CientSocket);
	WSACleanup();


	system("pause");
	return 0;
}