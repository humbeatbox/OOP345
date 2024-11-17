//Name:Hsiao-Kang Chang 
//Seneca email:hchang67@myseneca.ca
//Seneca Student ID:120049234
//2024-11-09 Creat this file
//Done on

//

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <string>
#include <iostream>

#include <string>
#include <vector>
#include <functional>
#include "mediaItem.h"

namespace seneca {
    class Collection {
        std::string m_name{};
        std::vector<MediaItem*> m_items{};
        void (*m_observer)(const Collection&, const MediaItem&){};

    public:
        Collection(const std::string& name);
        ~Collection();

        // Deleted copy/move constructors and assignment operators
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;

        // Queries
        const std::string& name() const;
        size_t size() const;

        // Observer registration
        void setObserver(void (*observer)(const Collection&, const MediaItem&));

        // Overloaded operators
        Collection& operator+=(MediaItem* item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;

        // Utility methods
        static std::string trimQuotes(const std::string& str);
        void removeQuotes();
        void sort(const std::string& field);
        friend std::ostream& operator<<(std::ostream& out, const Collection& collection);
    };
}


#endif //SENECA_COLLECTION_H
