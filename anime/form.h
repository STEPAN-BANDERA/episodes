#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPieSeries>
#include <QChart>
#include <QChartView>

#include <vector>
#include <map>


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
     void provideData(std::map<std::string, std::size_t> studiosStats, std::string nickname) noexcept;

private:
    Ui::Form *ui;
};

#endif // FORM_H
