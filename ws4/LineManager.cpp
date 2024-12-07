//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-28 Creat this file
//Done on

//
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

namespace seneca {

    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
        try {
            std::ifstream input(file);
            if (!input) {
                throw std::string("Unable to open file ") + file;
            }

            Utilities util;
            std::string record;//the whole life form file


            while (std::getline(input, record)) {//each line (one while loop)
                size_t pos = 0;
                bool more = true;

                //use the extractToken to extract the station name and set the more flag
                std::string current_name = util.extractToken(record, pos, more);

                //find the iterator of the current station
                auto current = std::find_if(stations.begin(), stations.end(),[&](Workstation* ws) { return ws->getItemName() == current_name; });

                if (current != stations.end()) {//not ned of this line (have other
                    m_activeLine.push_back(*current);

                    if (more) {
                        std::string next_name = util.extractToken(record, pos, more);
                        auto next = std::find_if(stations.begin(), stations.end(),[&](Workstation* ws) { return ws->getItemName() == next_name;});

                        if (next != stations.end()) {
                            (*current)->setNextStation(*next);//go to the next station
                        }
                    }
                }
            }

            m_cntCustomerOrder = g_pending.size();

        } catch (const std::string& msg) {
            throw msg;
        }
    }
//    void LineManager::reorderStations(){
//        m_firstStation = *std::find_if(m_activeLine.begin(), m_activeLine.end(),
//                                       [](Workstation* ws) { return ws->getNextStation() == nullptr; });
//    }
    void LineManager::reorderStations() {

        for (auto *first_candidate: m_activeLine) {//checkt all sttion
            bool first = true;//default is the first station
            for (auto *station: m_activeLine) {//if the station is not the first station
                if (station->getNextStation() == first_candidate) {
                    first = false;
                    break;
                }
            }
            //if the station is the first station set to the first station
            if (first) {
                m_firstStation = first_candidate;
                break;
            }
        }
        //order
        std::vector<Workstation *> ordered;
        Workstation *current = m_firstStation;
        while (current != nullptr) {
            ordered.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = ordered;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        iteration++;//need to add the iteration first

        os << "Line Manager Iteration: " << iteration << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto* station : m_activeLine) {
            station->fill(os);
        }

        for (auto* station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        return g_pending.empty() &&
               (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
    }
    void LineManager::display(std::ostream &os) const {
        for (auto *station: m_activeLine) {
            station->display(os);
        }
    }
}