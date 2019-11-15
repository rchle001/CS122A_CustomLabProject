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
    
    
    int x = GetSystemMetrics(SM_CXVIRTUALSCREEN)/2;
    int y = GetSystemMetrics(SM_CYVIRTUALSCREEN)/2;
    cout << "#" << endl;
    SetCursorPos(x, y);
    cout << "#" << endl;
    while(1)
    {
        
    }
    return 0;
}