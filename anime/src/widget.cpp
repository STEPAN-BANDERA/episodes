#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //this->allTitles.reserve(1000);
    //this->allUsersTitles.reserve(10);
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    this->ptableWidget = new QTableWidget;

    this->sortComboBox = new SortComboBox;
    this->pidComboBoxList = new QComboBox;

    this->pcallOpenLink  = new QPushButton("Open choosed profile");
    this->pcallDialogWindow = new QPushButton("Gеt input ids");
    this->pShowChartStudio = new QPushButton("Show Studio Charts");
    this->pShowChartGenre = new QPushButton("Show Genre Charts");
    this->pOpenJsonFile = new QPushButton("Add Data From File");
    this->pChangeLayoutButton = new QPushButton("Change to Black");
    

    this->pHorizontalbxLayout = new QHBoxLayout;


    this->pHorizontalButtonsLayout = new QHBoxLayout;
    this->pHorizontalButtonsLayout ->addWidget(this->pShowChartStudio);
    this->pHorizontalButtonsLayout ->addWidget(this->pShowChartGenre);
    this->pHorizontalButtonsLayout ->addWidget(this->pChangeLayoutButton);
    this->pVerticallbxLayout = new QVBoxLayout;



    this->pHorizontalbxLayout->addWidget(this->sortComboBox, 3);

    this->pHorizontalbxLayout->addWidget(this->pidComboBoxList, 3);
    this->pHorizontalbxLayout->addWidget(this->pcallOpenLink, 2);
    this->pHorizontalbxLayout->addWidget(this->pcallDialogWindow, 2);
    this->pHorizontalbxLayout->addWidget(this->pOpenJsonFile, 2);

    this->pVerticallbxLayout ->addWidget(this->ptableWidget);



    this->pVerticallbxLayout ->addLayout(this->pHorizontalButtonsLayout);
    this->pVerticallbxLayout ->addLayout(this->pHorizontalbxLayout); 
    this->setWindowTitle("Check profile");

    this->setLayout(this->pVerticallbxLayout);

    this->defaultStyleSheet = this->styleSheet();

    connect(pcallDialogWindow, SIGNAL (released()),this, SLOT (  GetInput()));
    //connect(pcallOpenLink,     SIGNAL (released()),this, SLOT (on_pushButton_2_clicked()));
    connect(pOpenJsonFile,     SIGNAL (released()),this, SLOT (  OpenFile()));
    connect(pShowChartStudio,  SIGNAL (released()),this, SLOT ( ShowStudioCharts()));
    connect(pChangeLayoutButton,  SIGNAL (released()),this, SLOT ( ChangeLayout()));

    //this->setCursor(QCursor(QPixmap(":/megumin-rotated.png")));
    //cursor = new AnimatedCursor(this, ":/gif/Awch.gif");
    std::atomic_init(&size, static_cast<std::uint32_t>(0));

    //this->ptableWidget->setSortingEnabled(true);
}

Widget::~Widget()
{
}

template <typename T>
const bool Contains( std::vector<T>& Vec, const T& Element )
{
    if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
        return true;

    return false;
}

void Widget::DownloadHtml(const QString page_address, QString &html_code)
{
    QNetworkAccessManager manager;
    QNetworkRequest request{QUrl{page_address}};
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    html_code = reply->readAll();
}

void Widget::do_work(const QString &e) noexcept
{
    qDebug() << QString("thread starts ") << e;
    std::vector<QString> watched_titles, favourite_titles;
    userInfo userIdInfo;
    QString tab_watched_html, tab_favourite_html;
    DownloadHtml(QString("https://yummyanime.club/users/id") + e + QString("?tab=watched"), tab_watched_html);
    DownloadHtml(QString("https://yummyanime.club/users/id") + e + QString("?tab=favourite"), tab_favourite_html);
    const std::int32_t pos_start_nickname = tab_watched_html.indexOf("Профиль "), pos_end_nickname = tab_watched_html.indexOf("</title>", pos_start_nickname);
    userIdInfo.nickname = tab_watched_html.mid(pos_start_nickname + 8,pos_end_nickname - pos_start_nickname - 8);
    userIdInfo.id = e;
    //const QRegularExpression rgx("<div class=\"update-list-flex\">[\\x{0000}-\\x{ffff}]{0,1000}<\\/div>[\x20\r\n]+<\\/div>");
    const QRegularExpression rgx("<li class=\"profile-list\" data-typeid=\"[0-9]\"[\\x{0000}-\\x{ffff}]{0,1500}<\\/li>");
    const QRegularExpression rgx2("<i\ class=\"fa\ fa-star\"></i>\ ([0-9.]+)");
    const QRegularExpression rgx3("\/catalog\/item\/([«»—0-9A-Za-z-]+)");
    const QRegularExpression rgx4("<li><a href=\"\/catalog\/category\/[A-Za-z-]+\">([\\x{0000}-\\x{ffff}]{0,40})<\/a><\/li>");
    const QRegularExpression rgx5("data-createdat=\"([0-9]+)\"");
    QRegularExpressionMatchIterator i = rgx.globalMatch(tab_watched_html);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch())
        {
            QString test = match.captured(0);
            QRegularExpressionMatchIterator i5 = rgx5.globalMatch(test);
            if (i5.hasNext())
            {
                QRegularExpressionMatch match5 = i5.next();
                QDateTime timestamp;
                timestamp.setTime_t(match5.captured(1).toInt());
                userIdInfo.date.push_back(timestamp);
            }
            QRegularExpressionMatchIterator i3 = rgx3.globalMatch(test);
            if (i3.hasNext())
            {
                QRegularExpressionMatch match3 = i3.next();
                watched_titles.push_back(match3.captured(0));
            }
            QRegularExpressionMatchIterator i2 = rgx2.globalMatch(test);
            while (i2.hasNext())
            {
                RatingInfo info;
                QRegularExpressionMatch match2 = i2.next();
                if (match2.hasMatch())
                    info.total_rating = match2.captured(1).toFloat();
                if (i2.hasNext())
                {
                    match2 = i2.next();
                    if (match2.hasMatch())
                        info.user_rating = match2.captured(1).toInt();
                }
                userIdInfo.ratingInfo.push_back(info);
            }
        }
    }


    /////////////////////////////////////////////////////////

    QRegularExpressionMatchIterator i6 = rgx.globalMatch(tab_favourite_html);
    while (i6.hasNext())
    {
        QRegularExpressionMatch match = i6.next();
        if (match.hasMatch())
        {
            QString test = match.captured(0);
            QRegularExpressionMatchIterator i3 = rgx3.globalMatch(test);
            if (i3.hasNext())
            {
                QRegularExpressionMatch match3 = i3.next();
                favourite_titles.push_back(match3.captured(0));
            }
        }
    }

    ///////////////////////////////////////////////////////////////

    for (std::size_t index = 0; index < watched_titles.size(); ++index){
        const auto &a = this->map.find(watched_titles[index]);
        if (this->map.cend() != a)
        {
            userIdInfo.titleInfo.push_back(a->second);
            continue;
        }
        //            QString image_path = "";
        //            pos_start = tab_watched_html.find("<img src=\"/img/posters/");
        
        //            while ( isdigit(tab_watched_html[pos_start + 23]))
        //            {
        //                image_path += tab_watched_html[pos_start + 23];
        //                ++pos_start;
        
        //            }
        //            image_path = ("https://yummyanime.club/img/posters/" + image_path + ".jpg");
        //            qDebug() << image_path.c_str();
        QNetworkAccessManager manager;
        QNetworkRequest request(QUrl((QString("https://yummyanime.club") + watched_titles[index])));
        QNetworkReply *reply(manager.get(request));
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        const QByteArray arr = reply->readAll().left(180000);
        const QString tab_watched_html = QString(arr);
        const std::int32_t pos_start_title = tab_watched_html.indexOf("<h1>",0);
        const std::int32_t end_start = tab_watched_html.indexOf("</h1>",pos_start_title + 4);
        QString sub_str = tab_watched_html.mid(pos_start_title + 4, end_start - pos_start_title - 4).replace("  ", "").remove(0,1);
        sub_str.chop(2);
        const std::int32_t pos_start_genre = tab_watched_html.indexOf("Жанр:");
        if (-1 == pos_start_genre) continue;
        const QStringRef check (&tab_watched_html, pos_start_genre, 2000);
        QRegularExpressionMatchIterator i4 = rgx4.globalMatch(check);
        std::vector<QString> genres;
        while (i4.hasNext())
        {
            QRegularExpressionMatch match4 = i4.next();
            if (match4.hasMatch())
                genres.push_back(match4.captured(1));
        }
        //tab_watched_html.erase(0,pos_start_genre);
        std::int32_t pos_start_studio = tab_watched_html.indexOf("Студия:");
        pos_start_studio = tab_watched_html.indexOf("<a href=\"/catalog/studio/", pos_start_studio);
        const std::int32_t pos_end_studio = tab_watched_html.indexOf("\">", pos_start_studio);
        QString studio = "";
        if (-1 != pos_end_studio)
            studio = tab_watched_html.mid(pos_start_studio + 25, pos_end_studio - pos_start_studio - 25);
        const std::int32_t pos_start_episodes = tab_watched_html.indexOf("Серии:");
        QString g (1, tab_watched_html[pos_start_episodes + 14]);
        if (pos_start_episodes != -1)
        {
            if (tab_watched_html[pos_start_episodes + 16].isDigit())
            {
                g.push_back(tab_watched_html[pos_start_episodes + 15]);
                g.push_back(tab_watched_html[pos_start_episodes + 16]);
            }
            else if (tab_watched_html[pos_start_episodes + 15].isDigit())
                g.push_back(tab_watched_html[pos_start_episodes + 15]);
        }
        if (g.toInt() != 801)
        {
            this->map.insert( this->map.begin(),{e, {sub_str, studio, static_cast<std::int32_t>(g.toInt()), 0, 0, genres, Contains(favourite_titles, watched_titles[index])}});
            userIdInfo.titleInfo.push_back({sub_str, studio, static_cast<std::int32_t>(g.toInt()), 0, 0, genres, Contains(favourite_titles, watched_titles[index])});
        }
        else
        {
            this->map.insert( this->map.begin(),{e, {sub_str, studio, static_cast<std::int32_t>(322), 0, 0, genres, Contains(favourite_titles, watched_titles[index])}});
            userIdInfo.titleInfo.push_back({sub_str, studio, static_cast<std::int32_t>(322), 0, 0, genres, Contains(favourite_titles, watched_titles[index])});
        }
    }
    this->userInfoVector.push_back(userIdInfo);
    this->size++;
    qDebug() << QString("thread download ends ") + e;
    this->FormTable();
}

void Widget::GetInput()
{
    QRegExp regex("[0-9]+");
    Dialog d(this);
    if (d.exec() == QDialog::Rejected) return;
    this->list.clear();
    this->ptableWidget->setRowCount(0);
    this->size.store(0);
    this->tp = std::chrono::system_clock::now();
    QString text = d.getText().toUtf8().constData() + QString("\n");
    qDebug() << text;
    this->list = text.split('\n');
    for (std::int32_t index = 0; index < this->list.size(); index++){
        if (regex.exactMatch(this->list.at(static_cast<int>(index))))
            std::thread(&Widget::do_work,this,this->list.at(static_cast<int>(index))).detach();
        else
            this->list.removeAt(static_cast<int>(index--));
    }
        //std::thread(&Widget::do_work,this,std::ref(tab_watched_html)).detach();
//    for(const auto & e : this->list)
//    {
//        //this->pidComboBoxList->addItem(QString::fromStdString("https://yummyanime.club/users/id" +e));
//        std::thread(&Widget::do_work,this,std::ref(e)).detach();
//        //auto a = std::async(&Widget::do_work, this, std::ref(e));
//    }

//    tbb::parallel_for(static_cast<std::int32_t>(0), idVector.size(),
//        [&](std::int32_t index) {
//           do_work(idVector[index]);
//        });
//    +        if (regex.exactMatch(this->list.at(static_cast<int>(index))))
//    +            ++this->size;
//    +    tbb::parallel_for(static_cast<std::int32_t>(0), this->list.size(),
//    +        [&](std::int32_t index)
//    +    {
//    +        if (regex.exactMatch(this->list.at(static_cast<int>(index))))
//    +            do_work(this->list.at(static_cast<int>(index)));
//    +    });
    //while (this->size.load() != this->list.size()) std::this_thread::yield();
    //this->FormLogFiles();
}

void Widget::AddRowsToTable(const QString &genres, const std::int32_t &row, const std::int32_t &current_index, const int &inner_index) noexcept
{
    auto item = new QTableWidgetItem(                  userInfoVector[current_index].titleInfo[inner_index].title         );
    if (userInfoVector[current_index].titleInfo[inner_index].is_favourite)
        item->setIcon(QIcon(":/images/2.ico"));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  1), item);
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  2),new QTableWidgetItem( QString::number( userInfoVector[current_index].ratingInfo[inner_index].total_rating)));
    if (userInfoVector[current_index].ratingInfo[inner_index].user_rating)
        this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index + 3),new QTableWidgetItem( QString::number( userInfoVector[current_index].ratingInfo[inner_index].user_rating )));
    else
        this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index + 3),new QTableWidgetItem( QString("")));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  4),new QTableWidgetItem( QString::number( userInfoVector[current_index].titleInfo[inner_index].episodes     )));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  5),new QTableWidgetItem( QString::number( userInfoVector[current_index].titleInfo[inner_index].episodes*20  )));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  6),new QTableWidgetItem( QString::number( userInfoVector[current_index].titleInfo[inner_index].episodes/3.  )));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  7),new QTableWidgetItem( QString::number( userInfoVector[current_index].titleInfo[inner_index].episodes/72. )));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  8),new QTableWidgetItem(                  userInfoVector[current_index].titleInfo[inner_index].studio        ));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index +  9),new QTableWidgetItem(                  genres                                                             ));
    this->ptableWidget->setItem  (row, static_cast<int>(COLUMN_COUNT*current_index + 10),new QTableWidgetItem(                  userInfoVector[current_index].date[inner_index].toString(Qt::SystemLocaleShortDate)));
}

void Widget::FormTable() noexcept
{
    lock_table_form_mux.lock();
    static std::int32_t current_index = -1;
    ++current_index;
    if(current_index == 0){
        QStringList lst;
        for(std::int32_t current_index = 0; current_index < this->list.size(); ++ current_index)
            lst << QString::number(current_index)
                << QString("тайтл")          << QString("общая оценка")   << QString("оценка пользователя")
                << QString("серии")          << QString("время в минутах")<< QString("время в часах")
                << QString("время в сутках") << QString("студия")         << QString("жанры")
                << QString("дата добавления")<< QString("");
        this->ptableWidget->setColumnCount(static_cast<int>(this->list.size()*COLUMN_COUNT));
        this->ptableWidget->setHorizontalHeaderLabels(lst);
    }
    QJsonArray json_array;
    for (std::int32_t inner_index = 0; inner_index < userInfoVector[current_index].titleInfo.size(); ++inner_index )
    {
        ++userInfoVector[current_index].studiosStats[userInfoVector[current_index].titleInfo[inner_index].studio].titles;
        userInfoVector[current_index].studiosStats[userInfoVector[current_index].titleInfo[inner_index].studio].episodes += userInfoVector[current_index].titleInfo[inner_index].episodes;
        bool b = 0;
        std::int32_t innerFoundIndex;
        for (const auto &elem: userInfoVector[current_index].titleInfo[inner_index].genres)
            userInfoVector[current_index].titleInfo[inner_index].genres_str += (elem + ", ");
        userInfoVector[current_index].titleInfo[inner_index].genres_str.chop(2);
        double averague = 0;
        std::int32_t counter = 0;
        for (std::int32_t index = 0; index < userInfoVector[current_index].ratingInfo.size(); ++index)
            if (0 != userInfoVector[current_index].ratingInfo[index].user_rating)
                averague += userInfoVector[current_index].ratingInfo[index].user_rating, ++counter;
        userInfoVector[current_index].averague = averague / counter;
        for (std::int32_t index_ = 0; index_ < current_index; ++index_ )
        {
            for (std::int32_t inner_index_ = 0; inner_index_ < userInfoVector[index_].titleInfo.size(); ++inner_index_ )
            {
                if(userInfoVector[current_index].titleInfo[inner_index].title == userInfoVector[index_].titleInfo[inner_index_].title)
                {
                    b = true;
                    innerFoundIndex = userInfoVector[index_].titleInfo[inner_index_].position;
                    goto skip;
                }
            }
        }
        skip:
        if(false == b)
        {
            this->ptableWidget->insertRow(this->ptableWidget->rowCount());
            userInfoVector[current_index].titleInfo[inner_index].position = this->ptableWidget->rowCount();
            AddRowsToTable(userInfoVector[current_index].titleInfo[inner_index].genres_str, this->ptableWidget->rowCount() - 1, current_index, inner_index);
        }
        else
        {
            userInfoVector[current_index].titleInfo[inner_index].position = innerFoundIndex;
            AddRowsToTable(userInfoVector[current_index].titleInfo[inner_index].genres_str, innerFoundIndex - 1, current_index, inner_index);
        }
        QJsonObject obj;
        obj["title"] = userInfoVector[current_index].titleInfo[inner_index].title;
        obj["episodes"] = QString::number(userInfoVector[current_index].titleInfo[inner_index].episodes);
        obj["studio"] = userInfoVector[current_index].titleInfo[inner_index].studio;
        obj["total rate"] = QString::number(userInfoVector[current_index].ratingInfo[inner_index].total_rating);
        obj["user rate"] = QString::number(userInfoVector[current_index].ratingInfo[inner_index].user_rating);
        obj["genres"] = userInfoVector[current_index].titleInfo[inner_index].genres_str;
        json_array.push_back(obj);
        userInfoVector[current_index].episode += userInfoVector[current_index].titleInfo[inner_index].episodes;
    }
    QString filename = QDir::currentPath() + QString("/") + QDateTime::currentDateTime().toString("yyyy.MM.dd") + QString("_")
                                            + QDateTime::currentDateTime().toString("hh.mm.ss") + QString("_") + this->list[current_index] + QString(".json");
    QJsonDocument document;
    document.setArray(json_array);
    QByteArray json_data = document.toJson();
    QFile output(filename);
    if (output.open(QIODevice::WriteOnly | QIODevice::Text)){
        output.write(json_data);
        output.close();
    }
    else qDebug() << "Cannot open file";
    userInfoVector[current_index].titles_ = static_cast<std::int32_t>(userInfoVector[current_index].titleInfo.size());
    if(current_index != this->list.size()-1){
        lock_table_form_mux.unlock();
        return;
    }
    for (std::int32_t current_index = 0; current_index < this->list.size(); ++current_index)
        for(const auto & a : userInfoVector[current_index].titleInfo)
            for( const auto & b : a.genres)
                ++userInfoVector[current_index].genresStats[b];
    this->ptableWidget->insertRow(0);
    for (std::int32_t var = 0; var < this->userInfoVector.size(); ++var)
    {
        QTableWidgetItem * w = new QTableWidgetItem(this->userInfoVector[var].nickname);
        w->setBackgroundColor(Qt::green);
        w->setIcon(QIcon(":/images/1.ico"));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var    ),w );
        //QTableWidgetItem::setData(Qt::BackgroundRole,QColor(255, 0, 0, 127));
        this->ptableWidget->setItem(1, static_cast<int>(COLUMN_COUNT*var    ),new QTableWidgetItem( this->userInfoVector[var].id  ));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var + 1),new QTableWidgetItem( QString("Всего: ") + QString::number(this->userInfoVector[var].titles_)));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var + 3),new QTableWidgetItem( QString("Средняя оценка: ") + QString::number(this->userInfoVector[var].averague)));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var + 4),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode    )));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var + 5),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode*20 )));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var + 6),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode/3. )));
        this->ptableWidget->setItem(0, static_cast<int>(COLUMN_COUNT*var + 7),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode/72.)));
    }
    //this->allTitles.erase(std::unique(this->allTitles.begin(),this->allTitles.end()),this->allTitles.end());
    //for (const auto & e : this->idVector) this->sortComboBox->addItem(QString::fromStdString( ("https://yummyanime.club/users/id" + e)  ));

    this->tp2 = std::chrono::system_clock::now();
    const std::chrono::duration<double> diff = tp2 - tp;
    qDebug() << diff.count();

    lock_table_form_mux.unlock();
}

void Widget::ShowStudioCharts() noexcept
{
    for(auto & e : this->userInfoVector){


        Form *pForm = new Form();
        pForm->setAttribute(Qt::WA_DeleteOnClose);
        pForm->provideData(&e.studiosStats, &e.genresStats, &e.ratingInfo, e.nickname, &e.date, &e.titleInfo);
        //std::thread([pForm](){
            pForm->processData();
        //}).detach();


        pForm->show();
    }

}


//void Widget::FormLogFiles() noexcept
//{
//    this->tp = std::chrono::system_clock::now();
//    boost::asio::thread_pool pool2(15);
//    for(std::int32_t current_index = 0; current_index < this->allUsersTitles.size() ; current_index++)
//    {
//        std::vector<std::pair<QString,std::pair<std::int32_t,std::int32_t>>> * a =&(allUsersTitles[current_index]);
//        boost::asio::post(pool2, [this, current_index, a]()
//        {
//            this->SaveFile(a, std::ref(idVector[current_index])) ;
//        } );
//    }
//    pool2.join();
//    this->tp2 = std::chrono::system_clock::now();
//    std::chrono::duration<double> diff = tp2 - tp;
//    qDebug( (std::to_string( diff.count() ).c_str() ));
//}


void Widget::OpenFile()
{
    QString json_filter = "JSON (*.json)";
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "/", json_filter, &json_filter,QFileDialog::DontUseNativeDialog);
    
    if(filename.isEmpty())
    {
    
    }
    else 
    {
        
        
        QFile file;
        file.setFileName(filename);
        file.open(QIODevice::ReadOnly | QIODevice::Text);


        QJsonParseError jsonError;
        QJsonDocument docJson = QJsonDocument::fromJson(file.readAll(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            qDebug() << jsonError.errorString();
        }
        QList<QVariant> list = docJson.toVariant().toList();
        QMap<QString, QVariant> map = list[0].toMap();
        qDebug() << map["title"].toString();
            
            
        //QMessageBox::about(this,tr("Error"), input.errorString());
    }
    //else
    {
        //QMessageBox::critical(this,tr("Error"), input.errorString());
    }
    
    
}

void Widget::ChangeLayout() noexcept
{
    if(this->defaultStyleSheet == this->styleSheet())
    {
        QFile styleSheetFile(":styles/Diffnes.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        this->setStyleSheet(styleSheet);
        this->pChangeLayoutButton->setText("Change to White");
    }
    else
    {
        this->setStyleSheet(this->defaultStyleSheet);
        this->pChangeLayoutButton->setText("Change to Black");
    }
}

//void Widget::on_pushButton_2_clicked()
//{
//    QDesktopServices::openUrl(QUrl(QString::fromStdString((this->pidComboBoxList->currentText().toStdString()))));
//}


//QRegularExpression  rgx2("[0-9.]+");
//    QFile file("out.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;

//    QTextStream out(&file);
//    out << tab_watched_html;
