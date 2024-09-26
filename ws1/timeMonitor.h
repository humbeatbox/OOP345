//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <string>
#include <chrono>
#include "event.h"

namespace seneca{
    class TimeMonitor{
        std::chrono::steady_clock::time_point m_startTime;
        std::string m_eventName;
    public:
        void startEvent(const char* name);
        Event stopEvent();
    };


}
#endif //SENECA_TIMEMONITOR_H