// Efimenko_lab1_Sem6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Efimenko_lab1_Sem6.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
vector <HANDLE> hEvents;

DWORD WINAPI Thread(LPVOID(lpParametr))
{
    int i = int(lpParametr);
    cout << i << " thread " << "start" <<endl;
    WaitForSingleObject(hEvents[i - 1], INFINITE);
    cout << i << " thread " << "done" << endl;
    return 0;
}

void start()
{
    int i = 1;

    HANDLE hStartEvent = CreateEvent(NULL, FALSE, FALSE, "StartEvent");
    HANDLE hStopEvent = CreateEvent(NULL, FALSE, FALSE, "StopEvent");
    HANDLE hConfirmEvent = CreateEvent(NULL, FALSE, FALSE, "ConfirmEvent");

    HANDLE hControlEvents[2] = { hStartEvent, hStopEvent };

    while (true)
    {
        int n = WaitForMultipleObjects(2, hControlEvents, FALSE, INFINITE) - WAIT_OBJECT_0; // В первом случае по возвращаемомуначению можно узнать, какой именно из объектов подал сигнал.
                                                                                             // Надо вычесть константу WAIT_OBJECT_0, и получится индекс в массиве lpHandles(hControlEvents)
        switch (n)
        {
        case 0:
                hEvents.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
                CreateThread(NULL, 0, Thread, (LPVOID)i, 0, NULL);
                SetEvent(hConfirmEvent); //Функция SetEvent() меняет состояние на сигнальное (есть событие)
                i++;
                break;
        case 1 :
            if (hEvents.size() == 0)
            {
                cout << "end of vector" << endl;
                Sleep(3000);
                SetEvent(hConfirmEvent);
                return;
            }
                cout << hEvents.back() << " is deleted" << endl;
                SetEvent(hEvents.back());
                hEvents.pop_back();
                i--;
                SetEvent(hConfirmEvent);
                break;
        }
    }
}



int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            start();
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
