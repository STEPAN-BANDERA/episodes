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

void Form::provideData(std::map<QString, StudioInfo> *studiosStats, std::map<QString, std::int32_t> *genresStats, const QString &nickname) noexcept
{
    this->stat = studiosStats;
    this->nickname = nickname;
    this->genresStats = genresStats;
}

QtCharts::QChart* Form::CreateChart(QPieSeries *series){
    QChart *chart = new QChart();
    chart->setGeometry(QRectF(0,0,1200,1000));
    chart->addSeries(series);
    //chart->setPlotArea(QRectF(200,0,1200,1000));
    //chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
    chart->legend()->detachFromChart();
    chart->legend()->setBackgroundVisible(true);
    chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
    chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
    chart->legend()->setGeometry(QRectF(20,20,350,950));
    chart->setTitle(this->nickname);
    chart->legend()->setAlignment(Qt::AlignLeft);
    //chart->legend()->attachToChart();
    return chart;
}

void Form::processData() noexcept
{
    srand(time(0));
    this->setWindowTitle(this->nickname);

    QPieSeries *series = new QPieSeries();
    QPieSeries *series2 = new QPieSeries();
    QPieSeries *series3 = new QPieSeries();
    for ( const auto & a : *this->stat){
        int r = rand()%255, g = rand()%255 , b = rand()%255;
        QPieSlice * slice = new QPieSlice();
        slice->setColor(QColor(r,g,b));
        slice->setValue(a.second.titles);
        slice->setLabel(a.first + QString(" ") + QString::number(a.second.titles));
        series->append(slice);

        QPieSlice * slice2 = new QPieSlice();
        slice2->setColor(QColor(r, g, b));
        slice2->setValue(a.second.episodes);
        slice2->setLabel(a.first + QString(" ") + QString::number(a.second.episodes));
        series2->append(slice2);
       }

    for ( const auto & a : *this->genresStats){
        int r = rand()%255, g = rand()%255 , b = rand()%255;
        QPieSlice * slice = new QPieSlice();
        slice->setColor(QColor(r,g,b));
        slice->setValue(a.second);
        slice->setLabel(a.first + QString(" ") + QString::number(a.second));
        series3->append(slice);
    }



    ui->graphicsView  ->setChart(CreateChart(series ));
    ui->graphicsView_2->setChart(CreateChart(series2));
    ui->graphicsView_3->setChart(CreateChart(series3));

}


void Form::on_pushButton_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}


void Form::on_pushButton_2_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}

void Form::on_pushButton_3_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}


