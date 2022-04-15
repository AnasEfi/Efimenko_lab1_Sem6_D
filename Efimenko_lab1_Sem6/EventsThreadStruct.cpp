#include "pch.h"
#include "EventsThreadStruct.h"

DWORD WINAPI Thread(LPVOID lpParametr)
{
    EventsThreadStruct* currentEvent = (EventsThreadStruct*)lpParametr; //тк LPVOID это указатель 
    int i = currentEvent->getCount();

    cout << i << " thread " << "start" << endl;
    WaitForSingleObject(currentEvent, INFINITE);
    cout << i << " thread " << "done" << endl;
    return 0; //честный возврат из потоковой функции
}

EventsThreadStruct EventsThreadStruct::getLastPair()
{
    return v_eventsThread.back();
}

void EventsThreadStruct::CreateNewPair(EventsThreadStruct& eventThreadPair)

{
    eventThreadPair.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (eventThreadPair.hEvent == NULL)
    {
        "Error while creating event";
    }
    eventThreadPair.hThread=CreateThread(NULL, 0, Thread, &eventThreadPair.hEvent, 0, NULL);
    v_eventsThread.push_back(eventThreadPair);
    ++count;
}

void EventsThreadStruct::DeletePair(EventsThreadStruct& eventThreadPair)
{
    if (CloseHandle(eventThreadPair.v_eventsThread.end()->hEvent) == 0)
        throw exception ("Cant close event");
    v_eventsThread.pop_back();
    --count;
}

HANDLE EventsThreadStruct::GetCurrentEvent()
{
    return v_eventsThread.end()->hEvent;
}



int EventsThreadStruct::getCount()
{
    return count;
}


