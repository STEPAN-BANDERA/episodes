#ifndef DATATYPES_H
#define DATATYPES_H
#include <string>
#include <vector>
#include <map>

struct StudioInfo
{
    std::size_t titles = 0;
    std::size_t episodes = 0;
};
struct TitleInfo
{
    std::string title;
    std::string studio;
    std::size_t episodes;
    std::size_t position;
    std::size_t rate;
    operator std::string() const {
        return title + " " + std::to_string(rate)+ " " + std::to_string(episodes) + " " + std::to_string(position) + " " + studio;
    }
};
struct userInfo
{
    std::map<std::string, StudioInfo> studiosStats;
    std::map<std::string, std::size_t> genresStats;
    double hours = 0.;
    double days = 0.;
    std::size_t titles_ = 0;
    std::size_t minuts = 0;
    std::size_t episode = 0;
    std::vector<TitleInfo> titleInfo;
    std::string nickname;
    std::string id;
};

#endif // DATATYPES_H
