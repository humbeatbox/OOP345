//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <string>
#include <chrono>
#include <ostream>
#include "settings.h"

namespace seneca {

    class Event {
        std::string m_name{};
        std::chrono::nanoseconds m_duration{};

    public:
        Event();
        Event(const char* name, const std::chrono::nanoseconds&);
        friend std::ostream& operator<<(std::ostream&, const Event&);
    };

}
#endif //SENECA_EVENT_H
