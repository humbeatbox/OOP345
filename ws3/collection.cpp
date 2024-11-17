//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//
//operator[] ,find_if_not
//operator+= ,find_if
//removeQuotes() ,for_each
//sort(const std::string& field) ,sort

#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <functional>
#include "collection.h"

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
        //check if item already exists or not using title
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
        //reverse find_if
        auto it = std::find_if_not(m_items.begin(), m_items.end(), [title](const MediaItem* item) {
            return item->getTitle() != title;
        });
        return (it != m_items.end()) ? *it : nullptr;
    }
    std::string Collection::trimQuotes(const std::string& str) {
        if (str.length() > 1 && str.front() == '\"' && str.back() == '\"') {
            return str.substr(1, str.length() - 2);
        } else if (str.length() > 1 && str.front() == '\"') {
            return str.substr(1);
        } else if (str.length() > 1 && str.back() == '\"') {
            return str.substr(0, str.length() - 1);
        }
        return str;
    }
    void Collection::removeQuotes() {
        std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
            item->setTitle(trimQuotes(item->getTitle()));
            item->setSummary(trimQuotes(item->getSummary()));
        });
    }

    void Collection::sort(const std::string& field) {
        //std::function for saving a lambda function prevent code duplication
        std::function<bool(const MediaItem*, const MediaItem*)> comparator{};

        if (field == "title") {
            comparator = [](const MediaItem* first, const MediaItem* second) {
                return first->getTitle() < second->getTitle();
            };
        } else if (field == "year") {
            comparator = [](const MediaItem* first, const MediaItem* second) {
                return first->getYear() < second->getYear();
            };
        } else if (field == "summary") {
            comparator = [](const MediaItem* first, const MediaItem* second) {
                return first->getSummary() < second->getSummary();
            };
        }

        std::sort(m_items.begin(), m_items.end(), comparator);
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