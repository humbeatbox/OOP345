//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//
#include <iomanip>
#include "event.h"

using namespace seneca;
using namespace std;
namespace seneca{
    Event::Event()= default;//a default constructor
    Event::Event(const char *name, const chrono::nanoseconds &duration):m_name(name), m_duration(duration) {
    }


    std::ostream& operator<<(std::ostream &os, const Event &event) {
        static int counter = 0;
        ++counter;

        os << setw(2) << counter << ": " << setw(40) << right << event.m_name << " -> ";

        //TODO adjust using chorno module
        if (g_settings.m_time_units == "seconds") {
            os << setw(2) << right << chrono::duration_cast<chrono::seconds>(event.m_duration).count() ;
        } else if (g_settings.m_time_units == "milliseconds") {
            os << setw(5) << right << chrono::duration_cast<chrono::milliseconds>(event.m_duration).count();
        } else if (g_settings.m_time_units == "microseconds") {
            os << setw(8) << right << chrono::duration_cast<chrono::microseconds>(event.m_duration).count();
        } else { // nanoseconds
            os << setw(11) <<right << chrono::duration_cast<chrono::nanoseconds>(event.m_duration).count();
        }
        os <<' ' << g_settings.m_time_units;

        return os;
    }
}



