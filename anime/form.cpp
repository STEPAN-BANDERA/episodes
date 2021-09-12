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

void Form::provideData(std::map<std::string, StudioInfo> *studiosStats, const std::string &nickname) noexcept
{
    this->stat = studiosStats;
    this->nickname = nickname;
}

void Form::processData() noexcept
{
    srand(time(0));
    QPieSeries *series = new QPieSeries();
    QPieSeries *series2 = new QPieSeries();
    for ( const auto & a : *this->stat){
        int r = rand()%255, g = rand()%255 , b = rand()%255;
        QPieSlice * slice = new QPieSlice();
        slice->setColor(QColor(r,g,b));
        slice->setValue(a.second.titles);
        slice->setLabel(a.first.c_str());
        series->append(slice);

        QPieSlice * slice2 = new QPieSlice();
        slice2->setColor(QColor(r, g, b));
        slice2->setValue(a.second.episodes);
        slice2->setLabel(a.first.c_str());
        series2->append(slice2);
       }

    QChart *chart = new QChart();
    QChart *chart2 = new QChart();
    //chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
    chart->addSeries(series);
    chart2->addSeries(series2);

    //chart->setPlotArea(QRectF(200,0,1400,1100));

    //chart->legend()->detachFromChart();
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
    chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
    //chart->legend()->setGeometry(QRectF(20,20,200,1000));
    chart->setTitle(QString::fromStdString(this->nickname));
    this->setWindowTitle(QString::fromStdString(this->nickname));
    chart->legend()->setAlignment(Qt::AlignLeft);

    //chart->legend()->attachToChart();
    ui->graphicsView->setChart(chart);


    //chart2->setAnimationOptions(QChart::AnimationOption::AllAnimations);


    //chart2->setPlotArea(QRectF(200,0,1400,1100));

    //chart2->legend()->detachFromChart();
    chart2->legend()->setBackgroundVisible(true);
    chart2->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
    chart2->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
    //chart2->legend()->setGeometry(QRectF(20,20,200,1000));
    chart2->setTitle(QString::fromStdString(this->nickname));
    chart2->legend()->setAlignment(Qt::AlignLeft);

    //chart->legend()->attachToChart();
    ui->graphicsView_2->setChart(chart2);


}


void Form::on_pushButton_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}


void Form::on_pushButton_2_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}
