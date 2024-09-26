//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#include "timeMonitor.h"

using namespace seneca;

namespace seneca{

    void TimeMonitor::startEvent(const char *name) {
        m_eventName = name;
        m_startTime = std::chrono::steady_clock::now();
    }

    Event TimeMonitor::stopEvent() {
        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);
        return Event(m_eventName.c_str(), duration);
    }

}
