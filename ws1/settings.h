//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-09-17 Creat this file
//Done on

//

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>


namespace seneca{

    struct Settings{
        bool  m_show_all{};
        bool m_verbose{};
        std::string m_time_units = "nanoseconds";
    };

    extern Settings g_settings;
}
#endif //SENECA_SETTINGS_H
