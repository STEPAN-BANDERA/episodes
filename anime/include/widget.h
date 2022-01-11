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
#include <QColor>

#include <regex>
#include <type_traits>
#include <algorithm>
#include <mutex>
#include <atomic>
#include <chrono>
#include <numeric>
#include <string>
#include <vector>
#include <regex>
#include "datatypes.h"
#include "animatedcursor.h"
#include <QFile>

//#ifndef Q_MOC_RUN
#define __TBB_NO_IMPLICIT_LINKAGE 1
#define __TBBMALLOC_NO_IMPLICIT_LINKAGE 1
#include "oneapi/tbb.h"
#include "tbb/concurrent_hash_map.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
//#endif

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
     void ChangeLayout() noexcept;
     //void on_pushButton_2_clicked();
     
private:
     tbb::concurrent_map <QString, TitleInfo> map;
     Form *pForm;
     QTableWidget * ptableWidget;
     QComboBox *pidComboBoxList;
     SortComboBox *sortComboBox;
     QPushButton *pcallDialogWindow, *pcallOpenLink, *pOpenJsonFile, *pShowChartStudio, *pShowChartGenre, *pChangeLayoutButton;
     QHBoxLayout *pHorizontalbxLayout, *pHorizontalButtonsLayout;
     QVBoxLayout *pVerticallbxLayout;
     std::atomic <std::uint32_t> size;
     //std::vector<QString> allTitles, allImages;
     QStringList list;
     void do_work(const QString &e) noexcept; 
     void FormTable() noexcept; 
     void AddRowsToTable(const QString &genres, const std::int32_t &row, const int &current_index, const int &inner_index) noexcept;
     void DownloadHtml(const QString page_address, QString &html_code);
     //void FormLogFiles(QJsonObject &json, const int &current_index, const std::int32_t &inner_index) noexcept;
     tbb::concurrent_vector <userInfo> userInfoVector;
     std::chrono::time_point <std::chrono::system_clock,std::chrono::duration<double>> tp,tp2;
     AnimatedCursor *cursor;
     std::mutex lock_table_form_mux;
     QString defaultStyleSheet;
};

#endif // WIDGET_H
