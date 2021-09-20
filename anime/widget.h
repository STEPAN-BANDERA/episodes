#ifndef WIDGET_H
#define WIDGET_H
#include <sortcombobox.h>
#include "dialog.h"
#include "form.h"
#include <QDebug>
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
//#include <boost/asio.hpp>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QChar>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>

#include <type_traits>
#include <algorithm>
#include <mutex>
#include <atomic>
#include <chrono>
#include <numeric>
#include <string>
#include <vector>
#include <regex>
#include "DataTypes.h"
#include "animatedcursor.h"

//#ifndef Q_MOC_RUN
#define __TBB_NO_IMPLICIT_LINKAGE 1
#define __TBBMALLOC_NO_IMPLICIT_LINKAGE 1
#include "oneapi\tbb.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
//#endif

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
     void ShowStudioCharts() noexcept;
     //void on_pushButton_2_clicked();
     
private:
     tbb::concurrent_map <std::string, TitleInfo> map;
     Form * pForm;
     QTableWidget * ptableWidget;
     QComboBox *pidComboBoxList;
     SortComboBox * sortComboBox;
     QPushButton * pcallDialogWindow, *pcallOpenLink, *pOpenJsonFile, *pShowChartStudio, *pShowChartGenre;
     QHBoxLayout * pHorizontalbxLayout, *pHorizontalButtonsLayout;
     QVBoxLayout * pVerticallbxLayout;
     std::atomic<uint32_t> size;
     std::vector<std::string> idVector , allTitles, allImages;
     void do_work(const std::string &e) noexcept; 
     void FormTable() noexcept; 
     //void FormLogFiles() noexcept; 
     //void SaveFile( const std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> * v,  std::string & str) noexcept;
     tbb::concurrent_vector<userInfo> userInfoVector;
     //std::vector <userInfo> userInfoVector;
     Ui::Widget *ui;
     std::chrono::time_point <std::chrono::system_clock,std::chrono::duration<double>> tp,tp2;
     AnimatedCursor *cursor;
};



#endif // WIDGET_H

    /*
     *
269705
729512
430622
676306
771703
486214
536964
454905
701345
    */
