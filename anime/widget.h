#ifndef WIDGET_H
#define WIDGET_H
#include <sortcombobox.h>
#include <QWidget>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>
#include <QString>
#include <QByteArray>
#include <QtWidgets>
#include <QScrollBar>
#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <algorithm>
#include <mutex>
#include <atomic>
#include <chrono>
#include <numeric>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <type_traits>

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
     void GetInput();
     void OpenFile();

     //void on_pushButton_2_clicked();
     
private:
     QTableWidget * ptableWidget;
     QComboBox *pidComboBoxList;
     SortComboBox * sortComboBox;
     QPushButton * pcallDialogWindow, *pcallOpenLink, *pOpenJsonFile;
     QHBoxLayout * pHorizontalbxLayout;
     QVBoxLayout * pVerticallbxLayout;
     std::vector<std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>>> allUsersTitles;
     std::vector<std::string> allTitles;
     std::mutex mux;
     std::atomic<std::size_t> size;
     std::vector <std::string> idVector;
     void do_work(const std::string &e) noexcept; 
     void SaveFile( const std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> * v,  std::string & str);
     struct userInfo
     {
         double hours = 0.;
         double days = 0.;
         std::size_t titles_ = 0;
         std::size_t minuts = 0;
         std::size_t episode = 0;
     };
     std::vector <userInfo> userInfoVector;
     Ui::Widget *ui;
};
#endif // WIDGET_H

    /*
     * 
771703
430622
486214
536964
454905
269705
701345
729512
676306
    
    */
