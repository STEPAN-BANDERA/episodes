#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>
#include <QString>
#include <QByteArray>
#include <string>
#include <vector>
#include <QtWidgets>
#include <QScrollBar>
#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <algorithm>
#include <mutex>
#include <atomic>
#include <chrono>
#include <numeric>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    
private slots:
     void on_pushButton_clicked();
     
private:
    std::vector<std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>>> allUsersTitles;
    std::mutex mux;
    std::atomic<std::size_t> size;
    void do_work(const std::string &e);
    struct userInfo
    {
        double hours = 0.;
        double days = 0.;
        std::size_t minuts = 0;
        std::size_t episode = 0;
    };
    std::vector <userInfo> userInfoVector;
    Ui::Widget *ui;
};
#endif // WIDGET_H
