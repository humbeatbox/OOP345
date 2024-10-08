//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
namespace seneca {


    class Logger {
        Event* m_events{};
        size_t m_size{};
    public:
        Logger();
        ~Logger();
        Logger(const Logger&)=delete;
        Logger& operator=(const Logger&)=delete;

        Logger(Logger&&) noexcept;
        Logger& operator=(Logger&&) noexcept;

        void addEvent(const Event&);

        friend std::ostream& operator<<(std::ostream&, const Logger&);
    };

}
#endif //SENECA_LOGGER_H
