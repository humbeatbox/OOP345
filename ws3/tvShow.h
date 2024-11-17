// Name:Hsiao-Kang Chang
// Seneca email:hchang67@myseneca.ca
// Seneca Student ID:120049234
// 2024-11-09 Creat this file
// Done on

//

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <string>
#include <list>
#include <sstream>
#include "mediaItem.h"
#include "settings.h"

namespace seneca
{
    class TvShow; // early declaration for TvEpisode can recognize TvShow

    // provided struct
    struct TvEpisode
    {
        const TvShow *m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem
    {


        int m_id{};
        //        title (inherited)
        //        the year of release (inherited)
        //        the summary (inherited)
        std::vector<TvEpisode> m_episodes{};
        TvShow(const int id, const std::string &title, unsigned short year, const std::string &summary, const std::vector<TvEpisode> &episodes); //: MediaItem(title, summary, year), m_id(id) {}
    public:
        static TvShow *createItem(const std::string &strShow);
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

        void display(std::ostream &out) const override;

       template <typename Collection_t>
        static void addEpisode(Collection_t &col, const std::string &strEpisode)
        {
            if (strEpisode.empty() || strEpisode[0] == '#')
            {
                throw "Not a valid episode.";
            }

            std::istringstream stream(strEpisode);
            std::string showId{}, episodeNumStr{}, seasonStr{}, episodeInSeasonStr{}, airDate{}, lengthStr{}, title{}, summary{};
            unsigned short episodeNum{}, season{}, episodeInSeason{};
            unsigned int showLength{};

            // 1.showID
            getline(stream, showId, ',');
            trim(showId);
            // 2.episode
            getline(stream, episodeNumStr, ',');
            trim(episodeNumStr);
            episodeNum = static_cast<unsigned short>(std::stoi(episodeNumStr));
            // 3.seasonNum
            getline(stream, seasonStr, ',');
            trim(seasonStr);
            season = seasonStr.empty() ? 1 : static_cast<unsigned short>(std::stoi(seasonStr));
            // 4.episodeInSeason
            getline(stream, episodeInSeasonStr, ',');
            trim(episodeInSeasonStr);
            episodeInSeason = static_cast<unsigned short>(std::stoi(episodeInSeasonStr));
            // 5.airDate
            getline(stream, airDate, ',');
            trim(airDate);
            // 6.length
            getline(stream, lengthStr, ',');
            trim(lengthStr);
            // 7.episode title
            getline(stream, title, ',');
            trim(title);
            // 8.episode summary
            getline(stream, summary);
            trim(summary);

            // convert lengthStr to unsigned
            if (!lengthStr.empty())
            {
                showLength = std::stoi(lengthStr.substr(0, 2)) * 3600 + std::stoi(lengthStr.substr(3, 2)) * 60 + std::stoi(lengthStr.substr(6, 2));
            }

            TvShow *show = nullptr;
            for (size_t i = 0; i < col.size(); ++i)
            {
                TvShow *tvShow = dynamic_cast<TvShow *>(col[i]);
                if (tvShow &&  tvShow->m_id == stoi(showId))
                {
                    show = tvShow;
                    break;
                }
            }

            TvEpisode episode = {show, episodeNum, season, episodeInSeason, airDate, showLength, title, summary};
            show->m_episodes.push_back(episode);
        }

    };
}
#endif // SENECA_TVSHOW_H
