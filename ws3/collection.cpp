//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//
#include "collection.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>

namespace seneca {
    Collection::Collection(const std::string& name) : m_name(name) {}

    Collection::~Collection() {
        for (auto* item : m_items) {
            delete item;
        }
    }

    const std::string& Collection::name() const {
        return m_name;
    }

    size_t Collection::size() const {
        return m_items.size();
    }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item) {
        if (!item) {
            return *this;
        }
        //check if item already exists or not
        auto it = std::find_if(m_items.begin(), m_items.end(), [item](const MediaItem* existingItem) {
            return existingItem->getTitle() == item->getTitle();
        });

        //doesn't find item in the collection
        if (it == m_items.end()) {
            m_items.push_back(item);
            if (m_observer) {
                m_observer(*this, *item);
            }
        } else {
            delete item; // Prevent memory leak if item already exists
        }

        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const {
        if (idx >= m_items.size()) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
        }
        return m_items[idx];
    }


    MediaItem* Collection::operator[](const std::string& title) const {
        //TODO do not use grab by reference?
//        auto it = std::find_if(m_items.begin(), m_items.end(), [&title](const MediaItem* item) {
//            return item->getTitle() == title;
//        });
        auto it = std::find_if(m_items.begin(), m_items.end(), [title](const MediaItem* item) {
            return item->getTitle() == title;
        });
        return (it != m_items.end()) ? *it : nullptr;
    }

    void Collection::removeQuotes() {
        std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
            auto title = item->getTitle();
            auto summary = item->getSummary();

            // Remove quotes from title if they are present at both ends and the length is greater than 1
            if (!title.empty() && title.front() == '\"' && title.back() == '\"' && title.length() > 1) {
                item->setTitle(title.substr(1, title.length() - 2));
            } else if (!title.empty() && title.front() == '\"' && title.length() > 1) {
                item->setTitle(title.substr(1));
            } else if (!title.empty() && title.back() == '\"' && title.length() > 1) {
                item->setTitle(title.substr(0, title.length() - 1));
            }

            // Remove quotes from summary if they are present at both ends and the length is greater than 1
            if (!summary.empty() && summary.front() == '\"' && summary.back() == '\"' && summary.length() > 1) {
                item->setSummary(summary.substr(1, summary.length() - 2));
            }else if (!summary.empty() && summary.front() == '\"' && summary.length() > 1) {
                item->setSummary(summary.substr(1));
            }else if (!summary.empty() && summary.back() == '\"' && summary.length() > 1) {
                item->setSummary(summary.substr(0, summary.length() - 1));
            }
        });
    }

    void Collection::sort(const std::string& field) {
        if (field == "title") {
            std::sort(m_items.begin(), m_items.end(), [](const MediaItem* a, const MediaItem* b) {
                return a->getTitle() < b->getTitle();
            });
        } else if (field == "year") {
            std::sort(m_items.begin(), m_items.end(), [](const MediaItem* a, const MediaItem* b) {
                return a->getYear() < b->getYear();
            });
        }else if(field== "summary"){
            std::sort(m_items.begin(), m_items.end(), [](const MediaItem* a, const MediaItem* b) {
                return a->getSummary() < b->getSummary();
            });
        }
    }
    std::ostream& operator<<(std::ostream& out, const Collection& collection) {
        for (size_t i = 0; i < collection.size(); ++i) {
            if (collection[i]) {
                out << *collection[i];
            }
        }
        return out;
    }
}