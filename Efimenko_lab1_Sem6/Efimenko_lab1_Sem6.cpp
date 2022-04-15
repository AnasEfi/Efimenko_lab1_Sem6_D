// Efimenko_lab1_Sem6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Efimenko_lab1_Sem6.h"
#include "EventsThreadStruct.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;


void start()
{
	int i = 1;

	HANDLE hStartEvent = CreateEvent(NULL, FALSE, FALSE, "StartEvent");
	HANDLE hStopEvent = CreateEvent(NULL, FALSE, FALSE, "StopEvent");
	HANDLE hConfirmEvent = CreateEvent(NULL, FALSE, FALSE, "ConfirmEvent");

	HANDLE hControlEvents[2] = { hStartEvent, hStopEvent };
	EventsThreadStruct events;

	while (true)
	{
		int n = WaitForMultipleObjects(2, hControlEvents, FALSE, INFINITE) - WAIT_OBJECT_0; // В первом случае по возвращаемомуначению можно узнать, какой именно из объектов подал сигнал.
																							 // Надо вычесть константу WAIT_OBJECT_0, и получится индекс в массиве lpHandles(hControlEvents)
		switch (n)
		{
		case 0:
			events.CreateNewPair(events);
			SetEvent(hConfirmEvent); //Функция SetEvent() меняет состояние на сигнальное (есть событие)
			break;
		case 1:
			if (events.getCount() == 0)
			{
				cout << "close programm" << endl;
				Sleep(3000);
				SetEvent(hConfirmEvent);
				return;
			}
			SetEvent(events.GetCurrentEvent());
			events.DeletePair(events);
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
