#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <sstream>

#include "wintab.h"

using namespace std;


int main()
{
    HWND wc;
    LPRECT rect;
    HINSTANCE hCurs1 = GetModuleHandle(NULL);

    fstream file;
    
    int x,y;
    int Lmouse;
    LPPOINT p;
    unsigned short z;
    
    GetCursorPos(p);

    /*x = GetSystemMetrics(SM_CXVIRTUALSCREEN)/2;       // gets half of horizontal distance
    y = GetSystemMetrics(SM_CYVIRTUALSCREEN)/2;*/       // gets half of vertical distance
    cout << "#" << endl;
    //SetCursorPos(x, y);
    cout << p->x << "\t" << p->y << endl;
    x = 765; y = 336;
    cout << "#" << endl;
    p->x = 765; p->y = 336; // this doesn't actually work to set cursor position, just sets p's position
    SetCursorPos(p->x, p->y); // this does though
    // z = GetAsyncKeyState(1);
    // cout << z << endl;
    Lmouse = 1; // leftclick mouse solution found at https://youtu.be/j4VFo4acorQ {Simulating Mouse and Keyboard Events - C++ Game Hacking Tutorial Part 2 | Click Bots}
    if(Lmouse)
    {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; // MOUSEEVENTF_{left, right, middle}DOWN
        SendInput(1, &input, sizeof(input));
        ZeroMemory(&input, sizeof(input));
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP; // MOUSEEVENTF_{left, right, middle}UP
        SendInput(1, &input, sizeof(input));
    }
    else
    {

    }
    while(1)
    {
        
    }
    return 0;
}