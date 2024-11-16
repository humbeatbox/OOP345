//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
namespace seneca {
    struct Settings {
        short m_maxSummaryWidth{80};
        bool m_tableView{};
    };

    extern Settings g_settings;
}

#endif //SENECA_SETTINGS_H
