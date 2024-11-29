//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-28 Creat this file
//Done on

//

#include "LineManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca {
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
        try {
            std::ifstream input(file);
            if (!input) {
                throw std::string("Unable to open file ") + file;
            }

            Utilities util;
            std::string record;

            // 關鍵改變：完全按照檔案順序處理每一行
            while (std::getline(input, record)) {
                size_t pos = 0;
                bool more = true;

                // 讀取當前工作站名稱
                std::string current_name = util.extractToken(record, pos, more);

                // 在 stations 中找到對應的工作站
                auto current = std::find_if(stations.begin(), stations.end(),
                                            [&](Workstation* ws) { return ws->getItemName() == current_name; });

                if (current != stations.end()) {
                    // 將當前工作站添加到 m_activeLine
                    m_activeLine.push_back(*current);

                    // 如果有下一個工作站，設定連接
                    if (more) {
                        std::string next_name = util.extractToken(record, pos, more);
                        auto next = std::find_if(stations.begin(), stations.end(),
                                                 [&](Workstation* ws) { return ws->getItemName() == next_name; });

                        if (next != stations.end()) {
                            (*current)->setNextStation(*next);
                        }
                    }
                }
            }

            m_cntCustomerOrder = g_pending.size();

        } catch (const std::string& msg) {
            throw msg;
        }
    }

    void LineManager::reorderStations() {

        std::vector<Workstation *> ordered;
        std::vector<bool> added(m_activeLine.size(), false);


        for (auto *first_candidate: m_activeLine) {
            bool is_first = true;
            for (auto *station: m_activeLine) {
                if (station->getNextStation() == first_candidate) {
                    is_first = false;
                    break;
                }
            }
            if (is_first) {
                m_firstStation = first_candidate;
                break;
            }
        }


        Workstation *current = m_firstStation;
        while (current != nullptr) {
            ordered.push_back(current);
            current = current->getNextStation();
        }


        m_activeLine = ordered;
    }
//    bool LineManager::run(std::ostream& os) {
//        static size_t iteration_count = 0;
//        iteration_count++;
//
//        os << "Line Manager Iteration: " << iteration_count << std::endl;
//        if (!g_pending.empty()) {
//            *m_firstStation += std::move(g_pending.front());
//            g_pending.pop_front();
//        }
//
//        for (auto* station : m_activeLine) {
//            station->fill(os);
//        }
//
//        for (auto* station : m_activeLine) {
//            station->attemptToMoveOrder();
//        }
//
//        // 只有當所有訂單都到達最終狀態時才返回true
//        return g_pending.empty() &&
//               (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
//
//    }
    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        iteration++;

        os << "Line Manager Iteration: " << iteration << std::endl;

        // 如果有待处理订单，移动一个到第一个工作站
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // 对每个工作站执行填充操作
        for (auto* station : m_activeLine) {
            station->fill(os);
        }

        // 尝试将订单移至下一工作站
        for (auto* station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        // 检查是否所有订单都已处理完成
        // 当所有订单都完成(在g_completed或g_incomplete中)时返回true
        return g_pending.empty() &&
               (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
    }
    void LineManager::display(std::ostream &os) const {
        for (auto *station: m_activeLine) {
            station->display(os);
        }
    }
}