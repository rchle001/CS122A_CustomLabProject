//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS

//#include "stdafx.h"
//#pragma comment(lib, "ws2_32.lib")
//#include <WinSock2.h>
//#include <ws2bth.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int main(const int argc, const char* argv[])
{
	const unsigned int sz = sizeof("connected")*2;
	char byte[sz] = { 0 };

	// opening file for comport / serial port
	HANDLE m_hcommPort = CreateFile("COM8", GENERIC_WRITE | GENERIC_READ, 0,0, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL, 0);
	if (m_hcommPort == INVALID_HANDLE_VALUE) 
	{
		DWORD error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND) cout << "file was not found" << endl;
		else {
			cout << error << endl;
		}
		return -1; 
	}

	// Getting comstate
	DCB dcbsp = { 0 };
	dcbsp.DCBlength = sizeof(dcbsp);
	if (!GetCommState(m_hcommPort, &dcbsp))
	{
		cout << GetLastError() << endl;
		return 1;
	}

	// setting port information
	dcbsp.BaudRate = CBR_9600;
	dcbsp.ByteSize = 8;
	dcbsp.StopBits = ONESTOPBIT;
	dcbsp.Parity = NOPARITY;

	if (!SetCommState(m_hcommPort, &dcbsp))
	{
		cout << GetLastError() << endl;
		return 2;
	}

	//setting commtimeouts
	// Doesn't seem to do anything useful, but it seems to 

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.ReadTotalTimeoutMultiplier = 5;
	//timeouts.WriteTotalTimeoutConstant = 100;
	//timeouts.WriteTotalTimeoutMultiplier = 10;
	
	if (!SetCommTimeouts(m_hcommPort, &timeouts))
	{
		cout << GetLastError() << endl;
		return 4;
	}

	DWORD dwBytesRead;
	INPUT lmouse;
	INPUT rmouse;
	INPUT mmouse;
	INPUT move;

	lmouse.type = INPUT_MOUSE;
	rmouse.type = INPUT_MOUSE;
	mmouse.type = INPUT_MOUSE;
	move.type = INPUT_MOUSE;

	while (1) {
		unsigned char direction=0;
		unsigned char buttons=0;
		unsigned char pressure=0;
		if (!ReadFile(m_hcommPort, byte, sizeof(byte), &dwBytesRead, NULL))
		{
			cout << GetLastError() << endl;
			CloseHandle(m_hcommPort);
			return -2;
		}
		if (dwBytesRead > 0) {
			cout << byte << endl;
			direction = byte[0] >> 4;
			buttons = (byte[0] >> 2) & 0x03;
			pressure = byte[0] & 0x03;
		}
		if (pressure > 0)
		{
			lmouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &lmouse, sizeof(lmouse));
			ZeroMemory(&lmouse, sizeof(lmouse));
		}
		else
		{
			lmouse.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &lmouse, sizeof(lmouse));
			ZeroMemory(&lmouse, sizeof(lmouse));
		}
		if (buttons > 0)
		{
			if (buttons & 0x01)
			{
				rmouse.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				SendInput(1, &rmouse, sizeof(rmouse));
				ZeroMemory(&rmouse, sizeof(rmouse));
			}
			else
			{
				rmouse.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
				SendInput(1, &rmouse, sizeof(rmouse));
				ZeroMemory(&rmouse, sizeof(rmouse));
			}
			if (buttons & 0x02)
			{
				mmouse.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
				SendInput(1, &mmouse, sizeof(mmouse));
				ZeroMemory(&mmouse, sizeof(mmouse));
			}
			else
			{
				mmouse.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
				SendInput(1, &mmouse, sizeof(mmouse));
				ZeroMemory(&mmouse, sizeof(mmouse));
			}
		}
		if (direction > 0)
		{
			move.mi.dwFlags = MOUSEEVENTF_MOVE;
			switch (direction)
			{
			case 0x0a:
				move.mi.dx = -25;
				move.mi.dy = -25;
				break;

			case 0x08:
				move.mi.dx = 0;
				move.mi.dy = -40;
				break;

			case 0x04:
				move.mi.dx = 0;
				move.mi.dy = 40;
				break;

			case 0x02:
				move.mi.dx = -40;
				move.mi.dy = 0;
				break;

			case 0x01:
				move.mi.dx = 40;
				move.mi.dy = 0;
				break;

			case 0x09:
				move.mi.dx = 25;
				move.mi.dy = -25;
				break;

			case 0x06:
				move.mi.dx = -25;
				move.mi.dy = 25;
				break;

			case 0x05:
				move.mi.dx = 25;
				move.mi.dy = 25;
				break;
				
			}
			SendInput(1, &move, sizeof(move));
			ZeroMemory(&move, sizeof(move));
		}
	}
	return 0;
}