//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#include "logger.h"

using namespace seneca;

namespace seneca{


    Logger::Logger() {
    }
    
    Logger::~Logger() {
        delete[] m_events;
        m_events = nullptr;
    }

    Logger::Logger(Logger &&other) noexcept: m_events(other.m_events), m_size(other.m_size)
    {  other.m_events = nullptr;
        other.m_size = 0;
    }

    Logger &Logger::operator=(Logger && other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] m_events;
        m_events = other.m_events;
        m_size = other.m_size;

        other.m_events = nullptr;
        other.m_size = 0;

        return *this;
    }

    void Logger::addEvent(const Event& event){
        Event* newEvents = new Event[m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            newEvents[i] = m_events[i];
        }
        newEvents[m_size] = event;

        m_size++;
        delete[] m_events;
        m_events = newEvents;
    }

    std::ostream &operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_size; ++i) {
            os << logger.m_events[i] << std::endl;
        }
        return os;
    }
}