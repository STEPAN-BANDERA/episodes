#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPushButton>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <vector>
#include <map>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QStackedWidget>
#include <QRectF>
#include <QRect>
#include <QLineSeries>
#include "DataTypes.h"
#include "chart.h"
#include "chartview.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void provideData(
            std::map<QString, StudioInfo> *studiosStats,
            std::map<QString, std::int32_t> *genresStats,
            std::vector<RatingInfo> *ratingInfo,
            const QString &nickname,
            std::vector<QDateTime> *date,
            std::vector<TitleInfo> *titleInfo
            ) noexcept;
    void processData() noexcept;
private:
    QLineSeries *setupLineSeries(
            bool is_label_visible,
            Qt::GlobalColor label_color,
            const QString &labels_format,
            Qt::GlobalColor series_color
            ) noexcept;
    QPieSlice *setupQPieSlice(
            qreal slice_value,
            const QString &slice_label,
            QColor slice_color = {rand()%255, rand()%255, rand()%255},
            bool is_slice_visible = 1
            ) noexcept;
    QChart *CreateChart(QPieSeries *series, const QString &title) noexcept;
    QChart *CreateChart(QLineSeries *series, const QString &title) noexcept;
    template <class T, class U>
    void insertPage(U *series) noexcept;

private slots:
    void moveToNextPage() noexcept;

    void moveToPrevPage() noexcept;

private:
    QPieSeries *studios_pie_series, *episodes_pie_series, *genres_pie_series, *marks_pie_series;
    QLineSeries *titles_line_series, *episodes_line_series;
    Chart *titles_line_chart, *episodes_line_chart;
    std::vector<QDateTime>* date;
    std::map<QString, StudioInfo> *stat;
    std::map<QString, std::int32_t> *genresStats;
    std::vector<RatingInfo> *ratingInfo;
    std::vector<TitleInfo> *titleInfo;
    QString nickname;
    std::int32_t total_titles = 0, total_episodes = 0, pages_amount = 0;
    Ui::Form *ui;
};

#endif // FORM_H
