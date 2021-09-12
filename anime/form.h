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
    void provideData(std::map<std::string, StudioInfo> *studiosStats, const std::string &nickname) noexcept;
    void processData() noexcept;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    std::map<std::string, StudioInfo>*  stat;
    std::string  nickname;
    Ui::Form *ui;
};

#endif // FORM_H
