#ifndef DATATYPES_H
#define DATATYPES_H
#define COLUMN_COUNT 12
#include <QString>
#include <vector>
#include <map>

struct StudioInfo
{
    std::int32_t titles = 0;
    std::int32_t episodes = 0;
};
struct RatingInfo{
    float total_rating = 0.;
    std::int32_t user_rating = 0;
};

struct TitleInfo
{
    QString title;
    QString studio;
    std::int32_t episodes;
    std::int32_t position;
    std::int32_t rate;
    operator QString() const {
        return title + QString(" ") + QString::number(rate)+ QString(" ") + QString::number(episodes) + QString(" ") + QString::number(position) + QString(" ") + studio;
    }
    std::vector<QString> genres;
};

struct userInfo
{
    std::map<QString, StudioInfo> studiosStats;
    std::map<QString, std::int32_t> genresStats;
    std::vector<QDateTime> date;
    double hours = 0.;
    double days = 0.;
    std::int32_t titles_ = 0;
    std::int32_t minuts = 0;
    std::int32_t episode = 0;
    std::vector<RatingInfo> ratingInfo;
    std::vector<TitleInfo> titleInfo;
    QString nickname;
    QString id;
};

#endif // DATATYPES_H
