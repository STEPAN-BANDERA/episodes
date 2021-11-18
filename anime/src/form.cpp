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
                       std::vector<RatingInfo> *ratingInfo,
                       const QString &nickname,
                       std::vector<QDateTime> *date,
                       std::vector<TitleInfo> *titleInfo
                       ) noexcept
{
    this->stat = studiosStats;
    this->nickname = nickname;
    this->genresStats = genresStats;
    this->ratingInfo = ratingInfo;
    this->date = date;
    this->titleInfo = titleInfo;
}

QLineSeries *Form::setupLineSeries(bool is_label_visible,
                           Qt::GlobalColor label_color,
                           const QString &labels_format,
                           Qt::GlobalColor series_color
                           ) noexcept
{
    QLineSeries *series = new QLineSeries();
    series->setPointLabelsVisible(is_label_visible);
    series->setPointLabelsColor(label_color);
    series->setPointLabelsFormat(labels_format);
    series->setColor(series_color);
    return series;
}

QPieSlice *Form::setupQPieSlice(
        qreal slice_value,
        const QString &slice_label,
        QColor slice_color,
        bool is_slice_visible
        ) noexcept
{
    QPieSlice *slice = new QPieSlice();
    slice->setLabelVisible(is_slice_visible);
    slice->setColor(slice_color);
    slice->setValue(slice_value);
    slice->setLabel(slice_label);
    return slice;
}

QChart *Form::CreateChart(QPieSeries *series, const QString &title) noexcept
{
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
    chart->setTitle(title);
    chart->legend()->setAlignment(Qt::AlignLeft);
    //chart->legend()->attachToChart();
    return chart;
}

QChart *Form::CreateChart(QLineSeries *series, const QString &title) noexcept
{
    QChart *chart = new Chart();
    chart->addSeries(series);
    chart->setTitle(title);
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();
    QDateTimeAxis *axisX1 = new QDateTimeAxis;
    axisX1->setFormat("dd-MM-yyyy h:mm:s");
    chart->setAxisX(axisX1, series);
    return chart;
}

void Form::processData() noexcept
{
    srand(time(0));
    std::int32_t i = 0, total_episodes = 0;
    this->setWindowTitle(this->nickname);
    this->studios_pie_series  = new QPieSeries();
    this->episodes_pie_series = new QPieSeries();
    this->genres_pie_series = new QPieSeries();
    this->marks_pie_series = new QPieSeries();
    this->episodes_line_series = this->setupLineSeries(true, Qt::black, "@yPoint", Qt::darkBlue);
    this->titles_line_series = this->setupLineSeries(true, Qt::black, "@yPoint", Qt::red);
    std::sort(this->date->begin(), this->date->end());
    for (std::size_t i = 0; i < this->date->size(); i++)
        this->titles_line_series->append((*this->date)[i].toMSecsSinceEpoch(), i);
    for (std::size_t i = 0; i < this->titleInfo->size(); i++){
        total_episodes += (*this->titleInfo)[i].episodes;
        this->episodes_line_series->append((*this->date)[i].toMSecsSinceEpoch(), total_episodes);
    }
    for (const auto &a : *this->stat){
        std::int32_t r = rand()%255, g = rand()%255, b = rand()%255;
        this->total_titles += a.second.titles;
        this->studios_pie_series ->append(this->setupQPieSlice(a.second.titles,   a.first + QString(" - ") + QString::number(a.second.titles  ), {r,b,g}));
        this->episodes_pie_series->append(this->setupQPieSlice(a.second.episodes, a.first + QString(" - ") + QString::number(a.second.episodes), {r,b,g}));
       }
    for (const auto &a : *this->genresStats)
        this->genres_pie_series->append(this->setupQPieSlice(a.second, a.first + QString(" - ") + QString::number(a.second)));
    std::map<std::int32_t, std::int32_t> rating;
    for ( const auto &a : *this->ratingInfo)
        ++rating[a.user_rating];
    for (const auto &a : rating)
        this->marks_pie_series->append(this->setupQPieSlice(a.second,  QString::number(a.first) + QString(" - ") + QString::number(a.second)));
    this->insertPage<QChartView, QPieSeries>(this->marks_pie_series);
    this->insertPage<QChartView, QPieSeries>(this->genres_pie_series);
    this->insertPage<QChartView, QPieSeries>(this->episodes_pie_series);
    this->insertPage<QChartView, QPieSeries>(this->studios_pie_series);
    this->insertPage<ChartView, QLineSeries>(this->titles_line_series);
    this->insertPage<ChartView, QLineSeries>(this->episodes_line_series);
    this->ui->stackedWidget->setCurrentIndex(0);
}

template <class T, class U>
void Form::insertPage(U *series) noexcept
{
    QPushButton *button_next = new QPushButton("Next"), *button_prev = new QPushButton("Previous");
    connect(button_next, SIGNAL(clicked()), this, SLOT(moveToNextPage()));
    connect(button_prev, SIGNAL(clicked()), this, SLOT(moveToPrevPage()));
    T *view = new T();
    const QString title = this->nickname + QString(" - ") + QString::number(this->total_titles);
    view->setChart(CreateChart(series, title));
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(button_next);
    vlayout->addWidget(button_prev);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(view);
    hlayout->addLayout(vlayout);
    QWidget * widget = new QWidget;
    widget->setLayout(hlayout);
    this->ui->stackedWidget->insertWidget(0, widget);
    ++pages_amount;
}

void Form::moveToNextPage() noexcept
{
    if (this->ui->stackedWidget->currentIndex() == pages_amount - 1)
        this->ui->stackedWidget->setCurrentIndex(0);
    else
        this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->currentIndex()+1);
}

void Form::moveToPrevPage() noexcept
{
    if (this->ui->stackedWidget->currentIndex() == 0)
        this->ui->stackedWidget->setCurrentIndex(pages_amount - 1);
    else
        this->ui->stackedWidget->setCurrentIndex(this->ui->stackedWidget->currentIndex()-1);
}
