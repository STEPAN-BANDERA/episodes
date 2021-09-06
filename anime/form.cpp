#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::provideData(std::map<std::string, size_t> studiosStats, std::string nickname) noexcept
{
    //    QBarSeries *series = new QBarSeries();
    //    for (const auto & e : this->userInfoVector ){
    //        QBarSet *set0 = new QBarSet("1");
    //        for ( const auto & a : e.studiosStats){
    //            *set0 << a.second;
    //        }

    //        //qDebug( (e.first.c_str() + std::to_string(e.second)).c_str());
    //    }
    //![1]
        QPieSeries *series = new QPieSeries();
        series->append("Jane", 1);
        series->append("Joe", 2);
        series->append("Andy", 3);
        series->append("Barbara", 4);
        series->append("Axel", 5);
    //![1]

    //![3]
        QChart *chart = new QChart();
        chart->addSeries(series);
    //![3]

    //![4]
        QChartView *chartView = new QChartView(chart);

        ui->graphicsView =chartView;
          ui->graphicsView->show();
}



