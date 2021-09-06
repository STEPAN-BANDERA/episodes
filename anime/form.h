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

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void provideStudioData(std::map<std::string, std::size_t> *studiosStats, const std::string &nickname) noexcept;
    void processStudioStats() noexcept;
private:
    std::vector<std::map<std::string, size_t>*>  stats;
    std::vector<std::string>  nicknames;
    Ui::Form *ui;
};

#endif // FORM_H
