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

void Form::provideData(std::map<QString, StudioInfo> *studiosStats,
                       std::map<QString, std::int32_t> *genresStats,
                       std::vector<RatingInfo>* ratingInfo,
                       const QString &nickname,
                       std::vector<QDateTime>* date
                       ) noexcept
{
    this->stat = studiosStats;
    this->nickname = nickname;
    this->genresStats = genresStats;
    this->ratingInfo = ratingInfo;
    this->date = date;
}

void Form::setupLineSeries(QLineSeries* series,
                           bool is_label_visible,
                           Qt::GlobalColor label_color,
                           const QString &labels_format,
                           Qt::GlobalColor series_color
                           ) noexcept
{
    series->setPointLabelsVisible(is_label_visible);
    series->setPointLabelsColor(label_color);
    series->setPointLabelsFormat(labels_format);
    series->setColor(series_color);
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
    chart->setTitle(this->nickname + QString("-") + QString::number(this->total_titles));
    chart->legend()->setAlignment(Qt::AlignLeft);
    //chart->legend()->attachToChart();
    return chart;
}

void Form::setupQPieSlice(
        QPieSlice * slice,
        bool is_slice_visible,
        QColor slice_color,
        qreal slice_value,
        const QString &slice_label
        ) noexcept
{
    slice->setLabelVisible(is_slice_visible);
    slice->setColor(slice_color);
    slice->setValue(slice_value);
    slice->setLabel(slice_label);
}

void Form::processData() noexcept
{
    srand(time(0));
    this->setWindowTitle(this->nickname);

    this->studios_pie_series  = new QPieSeries();
    this->episodes_pie_series = new QPieSeries();
    this->genres_pie_series = new QPieSeries();
    this->marks_pie_series = new QPieSeries();

    this->episodes_line_series = new QLineSeries();
    this->setupLineSeries(this->episodes_line_series, true, Qt::black, "@yPoint", Qt::darkBlue);

    this->titles_line_series = new QLineSeries();
    this->setupLineSeries(this->titles_line_series, true, Qt::black, "@yPoint", Qt::red);

    std::sort ((*this->date).begin(), (*this->date).end());
    for (std::size_t i = 0; i < (*this->date).size(); i++) {

        this->titles_line_series->append((*this->date)[i  ].toMSecsSinceEpoch(), i);
    }

    std::size_t i = 0;
    int32_t total_episodes = 0;
    for ( const auto & a : *this->stat){
        //qcharview

        int r = rand()%255, g = rand()%255 , b = rand()%255;
        QPieSlice * slice = new QPieSlice();
        this->setupQPieSlice(slice, 1, QColor(r,g,b), a.second.titles, a.first + QString(" ") + QString::number(a.second.titles));
        this->total_titles += a.second.titles;
        this->studios_pie_series->append(slice);
        QPieSlice * slice2 = new QPieSlice();
        this->setupQPieSlice(slice2, 1, QColor(r,g,b), a.second.episodes, a.first + QString(" ") + QString::number(a.second.episodes));
        this->episodes_pie_series->append(slice2);

        //chartview

        total_episodes +=  a.second.episodes;
        this->episodes_line_series->append((*this->date)[i++].toMSecsSinceEpoch(), total_episodes);

       }

    for ( const auto & a : *this->genresStats){
        int r = rand()%255, g = rand()%255 , b = rand()%255;
        QPieSlice * slice = new QPieSlice();
        slice->setLabelVisible(1);
        slice->setColor(QColor(r,g,b));
        slice->setValue(a.second);
        slice->setLabel(a.first + QString(" ") + QString::number(a.second));
        this->genres_pie_series->append(slice);
    }

    std::map<std::int32_t, std::int32_t> rating;
    for ( const auto & a : *this->ratingInfo){
        ++rating[a.user_rating];
    }
    for ( const auto & a : rating){
        int r = rand()%255, g = rand()%255 , b = rand()%255;
        QPieSlice * slice = new QPieSlice();
        slice->setLabelVisible(1);
        slice->setColor(QColor(r,g,b));
        slice->setValue(a.second);
        slice->setLabel(QString::number(a.first) + QString(" ") + QString::number(a.second));
        this->marks_pie_series->append(slice);
    }





    this->titles_line_chart = new Chart();
    this->titles_line_chart->addSeries(this->titles_line_series);
    this->titles_line_chart->setTitle("titles");
    this->titles_line_chart->setAnimationOptions(QChart::SeriesAnimations);
    this->titles_line_chart->legend()->hide();
    this->titles_line_chart->createDefaultAxes();
    QDateTimeAxis *axisX1 = new QDateTimeAxis;
    axisX1->setFormat("dd-MM-yyyy h:mm:s");
    this->titles_line_chart->setAxisX(axisX1, this->titles_line_series);


    this->episodes_line_chart = new Chart();
    this->episodes_line_chart->addSeries(this->episodes_line_series);
    this->episodes_line_chart->setTitle("episodes");
    this->episodes_line_chart->setAnimationOptions(QChart::SeriesAnimations);
    this->episodes_line_chart->legend()->hide();
    this->episodes_line_chart->createDefaultAxes();
    QDateTimeAxis *axisX2 = new QDateTimeAxis;
    axisX2->setFormat("dd-MM-yyyy h:mm:s");
    this->episodes_line_chart->setAxisX(axisX2, this->episodes_line_series);

//    ChartView *chartView = new ChartView(/*chart*/);
//    chartView->setRenderHint(QPainter::Antialiasing);




//    auto a = ui->stackedWidget->widget(1);
//    a->


    ui->graphicsView_6->setChart(titles_line_chart);

    ui->graphicsView  ->setChart(CreateChart(this->studios_pie_series ));
    ui->graphicsView_2->setChart(CreateChart(this->episodes_pie_series));
    ui->graphicsView_3->setChart(CreateChart(this->genres_pie_series));
    ui->graphicsView_4->setChart(CreateChart(this->marks_pie_series));
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
    this->ui->stackedWidget->setCurrentIndex(3);
}



void Form::on_pushButton_4_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(4);
}


void Form::on_pushButton_5_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}


void Form::on_pushButton_6_clicked() // this is not page swap
{
    ui->graphicsView_6->setChart(episodes_line_chart);
}

