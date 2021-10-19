#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <vector>
#include <map>
#include <QStackedWidget>
#include <QtGlobal>
#include <QRectF>
#include <QRect>
#include <QLineSeries>
#include <QValueAxis>
#include <QMouseEvent>
#include <QRubberBand>
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
    void provideData(std::map<QString, StudioInfo> *studiosStats,
                     std::map<QString, std::int32_t> *genresStats,
                     std::vector<RatingInfo>* ratingInfo,
                     const QString &nickname) noexcept;
    void processData() noexcept;
    QtCharts::QChart* CreateChart(QtCharts::QPieSeries *series);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:

    std::map<QString, StudioInfo>*  stat;
    std::map<QString, std::int32_t>* genresStats;
    std::vector<RatingInfo>* ratingInfo;
    QString  nickname;
    std::int32_t total_titles = 0;
    std::int32_t total_episodes = 0;
    Ui::Form *ui;
};

#endif // FORM_H
