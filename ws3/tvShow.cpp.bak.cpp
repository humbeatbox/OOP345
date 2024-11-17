// Name:Hsiao-Kang Chang
// Seneca email:hchang67@myseneca.ca
// Seneca Student ID:120049234
// 2024-11-09 Creat this file
// Done on

//
#include <iomanip>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "tvShow.h"
namespace seneca
{
    TvShow::TvShow(const int id, const std::string &title, unsigned short year, const std::string &summary, const std::vector<TvEpisode>& episodes)
        : MediaItem(title, summary, year), m_id(id), m_episodes(episodes) {}

    void TvShow::display(std::ostream &out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto &item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    TvShow *TvShow::createItem(const std::string &strShow){
        if (strShow.empty() || strShow[0] == '#'){
            throw "Not a valid show.";
        }
        std::vector<TvEpisode> episodes{};
        std::istringstream stream(strShow);
        std::string idStr, title, yearStr, summary;
        int id{};
        unsigned short year;
        try{
            getline(stream, idStr, ',');
            trim(idStr);
            id = static_cast<int>(std::stoi(idStr));
            getline(stream, title, ',');
            trim(title);
            getline(stream, yearStr, ',');
            trim(yearStr);
            year = static_cast<unsigned short>(stoi(yearStr));
            getline(stream, summary);
            trim(summary);
        }
        catch (...)
        {
            throw "Not a valid show.";
        }
        return new TvShow(id, title, year, summary, episodes);
    }

    double TvShow::getEpisodeAverageLength() const{
        if (m_episodes.empty()){
            return 0.0; // Avoid division by zero
        }

        double totalLength = accumulate(m_episodes.begin(), m_episodes.end(), 0.0,[](double sum, const TvEpisode &episode){
            return sum + episode.m_length;
        });

        return totalLength / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const{
        std::list<TvEpisode> filteredEpisodes;

        // Filter episodes that are at least 1 hour (3600 seconds) long
        copy_if(m_episodes.begin(), m_episodes.end(), back_inserter(filteredEpisodes),[](const TvEpisode &episode){
                    return episode.m_length >= 3600;
        });

        std::list<std::string> longEpisodes;

        // Transform filtered episodes to extract the titles
        transform(filteredEpisodes.begin(), filteredEpisodes.end(), back_inserter(longEpisodes),[](const TvEpisode &episode){
                      return episode.m_title;
        });

        return longEpisodes;
    }

}
