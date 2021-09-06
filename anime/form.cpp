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

void Form::provideStudioData(std::map<std::string, size_t> *studiosStats, const std::string &nickname) noexcept
{
    this->stats.push_back(studiosStats);
    this->nicknames.push_back(nickname);
}

void Form::processStudioStats() noexcept
{
    srand(time(0));
    QPieSeries *series = new QPieSeries();

//    for (const auto & e : this->stats ){
//        //QBarSet *set0 = new QBarSet("1");
//        for ( const auto & a : *e){
//            //*set0 << a.second;
//            qDebug( (a.first + " " + std::to_string(a.second)).c_str());
//            }
//    }

    for ( const auto & a : *this->stats[0]){
        QPieSlice * slice = new QPieSlice();
        slice->setColor(QColor(rand()%255, rand()%255, rand()%255));
        slice->setValue(a.second);
        slice->setLabel(a.first.c_str());
        series->append(slice);
       }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(this->nicknames[0]));

    ui->graphicsView = new QChartView(chart);
        //![4]
    //ui->stackedWidget->  =chartView;
    ui->graphicsView->show();

//    std::vector<QWidget *> widgetVec;
//    QStackedWidget *stackedWidget = new QStackedWidget;

//    for(std::size_t index = 0; index < this->stats.size(); ++index){
//        QWidget *w = new QWidget;
//        w->ad
//        widgetVec.push_back(w);
//        stackedWidget->addWidget(widgetVec[index]);
//    }

//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(stackedWidget, 0);
//    this->setLayout(layout);

}



