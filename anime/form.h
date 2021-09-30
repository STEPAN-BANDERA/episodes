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
#include "DataTypes.h"

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
                     const QString &nickname) noexcept;
    void processData() noexcept;
    QtCharts::QChart* CreateChart(QtCharts::QPieSeries *series);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    std::map<QString, StudioInfo>*  stat;
    std::map<QString, std::int32_t> *genresStats;
    QString  nickname;
    Ui::Form *ui;
};

#endif // FORM_H
