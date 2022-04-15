#pragma once
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
using namespace std;

struct EventsThreadStruct
{
	private:
		
		static vector <EventsThreadStruct> v_eventsThread;
		int count;
		HANDLE hThread;
		HANDLE hEvent;
	public:
		EventsThreadStruct getLastPair();
		void CreateNewPair(EventsThreadStruct&);
		void DeletePair(EventsThreadStruct&);
		HANDLE GetCurrentEvent();
		int getCount();

		/*HANDLE GetEvent();
		HANDLE GetThread();*/

	};

