#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <ws2bth.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#define PORT 8

const char szHost[] = "246f280b7b06";

using namespace std;

int main(const int argc, const char* argv[])
{
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		return 1;
	}
	SOCKET blu = socket(AF_BTH, SOCK_STREAM, 3);
	if (blu < 0)
		return 2;
	/*
	SOCKADDR_BTH sin;
	ZeroMemory(&sin, sizeof(sin));
	sin.addressFamily = AF_BTH;
	sin.
	memcpy(&sin.sin_addr.S_un.S_addr, host->h_addr_list[0], sizeof(sin.sin_addr.S_un.S_addr));
	if (connect(blu, (const sockaddr*)&sin, sizeof(sin)) != 0)
		return 4;
	*/
	//SOCKADDR_BTH sockAddr;
	//SOCKET btSocket;
	//int error;

	//btSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	//memset(&sockAddr, 0, sizeof(sockAddr));
	//sockAddr.addressFamily = AF_BTH;
	//sockAddr.serviceClassId = RFCOMM_PROTOCOL_UUID;
	//sockAddr.port = BT_PORT_ANY;
	//WSAQUERYSET querySet;
	//memset(&querySet, 0, sizeof(querySet));
	//querySet.dwSize = sizeof(querySet);
	//querySet.dwNameSpace = NS_BTH;
	//HANDLE hLookup;
	//if (0 != WSALookupServiceBegin(&querySet, LUP_CONTAINERS | LUP_FLUSHCACHE | LUP_RETURN_TYPE, &hLookup))
	//{
	//	if (WSAGetLastError() != WSASERVICE_NOT_FOUND)
	//	{
	//		// error during WSALookupServiceBegin
	//	}
	//	else
	//	{
	//		//No BlueTooth device Found
	//	}
	//	return -1;
	//}
	//const unsigned int dlsize = 2000;
	//DWORD deviceLength = dlsize;
	//char buf[dlsize];
	//WSAQUERYSET* pDevice = PWSAQUERYSET(buf); //pDevice->lpServiceClassId = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
	//while (0 == WSALookupServiceNext(hLookup, LUP_RETURN_ADDR | LUP_RETURN_NAME | LUP_RES_SERVICE | LUP_RETURN_TYPE, (LPDWORD)&deviceLength, pDevice))
	//{
	//	PSOCKADDR_BTH sa = PSOCKADDR_BTH(pDevice->lpcsaBuffer->RemoteAddr.lpSockaddr);
	//	if (sa->addressFamily != AF_BTH)
	//	{
	//		// Address family is not AF_BTH  for bluetooth device discovered
	//		continue;
	//	}
	//	//the name is available in pDevice->lpszServiceInstanceName
	//	//the MAC address is available in sa->btAddr
	//	cout << pDevice->lpszServiceInstanceName << "\t" << sa->btAddr <<  "\t"  << pDevice->lpServiceClassId << endl;
	//	if (pDevice->lpszServiceInstanceName == "esps") {
	//		sockAddr.btAddr = sa->btAddr; 
	//		cout << sockAddr.btAddr << " " << endl;  break;
	//	}
	//}
	//WSALookupServiceEnd(hLookup);
	//cout << sockAddr.btAddr << endl;
	////sockAddr.btAddr = 
	//	error = connect(btSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	//char szBuffer[200];
	//char szTemp[200];
	////while (recv(blu, szTemp, 200, 0))
	//{
	//	recv(blu, szTemp, 200, 0);
	//	cout << szTemp << endl;
	//}
	//	//strcat(szBuffer, szTemp);

	//printf("%s\n", szBuffer);

	//closesocket(blu);
	//getchar();
	const unsigned int sz = 1000;
	bool read; char byte[sz];
	HANDLE m_hcommPort = ::CreateFile("COM8", GENERIC_WRITE | GENERIC_READ, 0,0, OPEN_EXISTING, 0, 0);
	if (m_hcommPort == INVALID_HANDLE_VALUE) { cout << GetLastError() << endl; return -1; }
	while (1) {
		read = ::ReadFile(m_hcommPort, byte, sizeof(byte), NULL, NULL);
		cout << byte[0] + '0' << endl;
	}
	return 0;
}