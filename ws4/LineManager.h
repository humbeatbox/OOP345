//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-28 Creat this file
//Done on

//

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include <vector>
#include <string>
#include "Workstation.h"

namespace seneca {
    class LineManager {
        std::vector<Workstation*> m_activeLine{};//the collection of workstations for the current assembly line.
        size_t m_cntCustomerOrder{};//the total number of CustomerOrder objects
        Workstation* m_firstStation{};//points to the first active station on the current line

    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif //SENECA_LINEMANAGER_H
