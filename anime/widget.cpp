#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->ui->setupUi(this);
    this->allTitles.reserve(1000);
    //this->allUsersTitles.reserve(10);
    this->ptableWidget = new QTableWidget;

    this->sortComboBox = new SortComboBox;
    this->pidComboBoxList = new QComboBox;

    this->pcallOpenLink  = new QPushButton("Open choosed profile");
    this->pcallDialogWindow = new QPushButton("Gеt input ids");
    this->pShowChartStudio = new QPushButton("Show Studio Charts");
    this->pShowChartGenre = new QPushButton("Show Genre Charts");
    this->pOpenJsonFile = new QPushButton("Add Data From File");
    

    this->pHorizontalbxLayout = new QHBoxLayout;


    this->pHorizontalButtonsLayout = new QHBoxLayout;
    this->pHorizontalButtonsLayout ->addWidget(this->pShowChartStudio);
    this->pHorizontalButtonsLayout ->addWidget(this->pShowChartGenre);
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

    connect(pcallDialogWindow, SIGNAL (released()),this, SLOT (  GetInput()));
    //connect(pcallOpenLink,     SIGNAL (released()),this, SLOT (on_pushButton_2_clicked()));
    connect(pOpenJsonFile,     SIGNAL (released()),this, SLOT (  OpenFile()));
    connect(pShowChartStudio,  SIGNAL (released()),this, SLOT ( ShowStudioCharts()));

    //this->setCursor(QCursor(QPixmap(":/megumin-rotated.png")));
    //cursor = new AnimatedCursor(this, ":/Awch.gif");
    std::atomic_init(&size, (uint32_t)0);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_work(const QString &e) noexcept
{
    qDebug() << QString("thread starts ") << e;
    std::vector<TitleInfo> titles;
    std::vector<QString> vct2;
    std::vector<std::wstring> vct;
    userInfo userIdInfo;
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(QString("https://yummyanime.club/users/id") + e + QString("?tab=watched")));
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    const QString str = QString(reply->readAll());
    const std::int32_t pos_start_nickname = str.indexOf("Профиль "), pos_end_nickname = str.indexOf("</title>", pos_start_nickname);
    userIdInfo.nickname = str.mid(pos_start_nickname + 8,pos_end_nickname - pos_start_nickname - 8);
    userIdInfo.id = e;
    QRegularExpression  rgx("<div class=\"update-list-flex\">[\\x{0000}-\\x{ffff}]{0,1000}<\\/div>[\x20\r\n]+<\\/div>");
    QRegularExpression  rgx2("<i\ class=\"fa\ fa-star\"></i>\ ([0-9.]+)");
    QRegularExpression  rgx3("\/catalog\/item\/([«»—0-9A-Za-z-]+)");
    //QRegularExpression  rgx2("[0-9.]+");
//    QFile file("out.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;

//    QTextStream out(&file);
//    out << str;


//    QRegularExpressionMatchIterator i = rgx.globalMatch(str);
//    while (i.hasNext()) {
//        QRegularExpressionMatch match = i.next();
//        if (match.hasMatch()) {
//            QString test = match.captured(0);
//            QRegularExpressionMatchIterator i2 = rgx2.globalMatch(test);
//            while (i2.hasNext()) {
//                QRegularExpressionMatch match2 = i2.next();
//                if (match2.hasMatch()) {
//                     qDebug() << match2.captured(0);
//                }
//            }
//        }
//    }
    QRegularExpressionMatchIterator i3 = rgx3.globalMatch(str);
    while (i3.hasNext()) {
        QRegularExpressionMatch match3 = i3.next();
        if (match3.hasMatch()) {
             vct2.push_back(match3.captured(0));
        }
    }
    for (const auto & e : vct2){
        const auto &a = this->map.find(e);
        if (this->map.cend() != a){
            userIdInfo.titleInfo.push_back(a->second);
            continue;
        }
        //            QString image_path = "";
        //            pos_start = str.find("<img src=\"/img/posters/");
        
        //            while ( isdigit(str[pos_start + 23]))
        //            {
        //                image_path += str[pos_start + 23];
        //                ++pos_start;
        
        //            }
        //            image_path = ("https://yummyanime.club/img/posters/" + image_path + ".jpg");
        //            qDebug() << image_path.c_str();

        QNetworkRequest request(QUrl((QString("https://yummyanime.club") + e)));
        QNetworkReply *reply(manager.get(request));
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        const QByteArray arr = reply->readAll().left(180000);
        const QString str = QString(arr);
        const std::int32_t pos_start_title = str.indexOf("<h1>",0);
        const std::int32_t end_start = str.indexOf("</h1>",pos_start_title + 4);
        QString sub_str = str.mid(pos_start_title + 4, end_start - pos_start_title - 4);
        std::int32_t doubleSpace = sub_str.indexOf("  ");
        while (doubleSpace != -1)
        {
            sub_str.remove(doubleSpace, 2);
            doubleSpace = sub_str.indexOf("  ");
        }
        sub_str.chop(2);
        sub_str.remove(0,1);
        //str.erase(0,pos_start_title);
        std::int32_t pos_start_genre = str.indexOf("Жанр:");
        QString check = str.mid(pos_start_genre, 2000);
//        std::regex rgx("<li><a href=\"\/catalog\/category\/[A-Za-z-]+\">(.*)<\/a><\/li>");
//        std::smatch matches;
//        while (std::regex_search(check, matches, rgx)){
//            ++userIdInfo.genresStats[matches[1].str()];
//            check.erase(0,matches[0].str().size()+45);
//        }
        //str.erase(0,pos_start_genre);
        std::int32_t pos_start_studio = str.indexOf("Студия:");
        pos_start_studio = str.indexOf("<a href=\"/catalog/studio/", pos_start_studio);
        const std::int32_t pos_end_studio = str.indexOf("\">", pos_start_studio);
        QString studio = "";
        if(-1 != pos_end_studio)
            studio = str.mid(pos_start_studio + 25, pos_end_studio - pos_start_studio - 25);
        const std::int32_t pos_start_episodes = str.indexOf("Серии:");
        QString g (1, str[pos_start_episodes + 19]);
        if(pos_start_episodes != -1){
            if (str[pos_start_episodes + 21].isDigit())
            {
                g.push_back(str[pos_start_episodes + 20]);
                g.push_back(str[pos_start_episodes + 21]);
            }
            else if (str[pos_start_episodes + 20].isDigit())
                g.push_back(str[pos_start_episodes + 20]);
        }
        this->map.insert( this->map.begin(),{e, {sub_str, studio,static_cast<std::int32_t>(g.toInt()),0,0 }});
        userIdInfo.titleInfo.push_back({sub_str, studio,static_cast<std::int32_t>(g.toInt()),0,0 });
    }
    this->userInfoVector.push_back(userIdInfo);
    this->size++;
    qDebug() << QString("thread ends ") + QString(e);
}

void Widget::GetInput()
{
    QRegExp regex("[0-9]+");
    Dialog d(this);
    if(d.exec() == QDialog::Rejected) return;
    this->list.clear();
    this->ptableWidget->setRowCount(0);
    this->size.store(0);
    this->tp = std::chrono::system_clock::now();
    QString text = (d.getText().toUtf8().constData() + QString("\n"));
    qDebug() << text;
//    std::int32_t pos;
    this->list = text.split('\n');
//    for (std::int32_t index = 0; index < idVector.size(); ++index){
//        if(!std::regex_match(idVector[index],re)){
//            idVector.erase(idVector.begin()+index--);
//        }
//    }
    QString str;
    for (std::int32_t index = 0; index < this->list.size(); index++){
        //std::thread(&Widget::do_work,this,std::ref(str)).detach();
        if(regex.exactMatch(this->list.at(static_cast<int>(index)))){
            std::thread(&Widget::do_work,this,this->list.at(static_cast<int>(index))).detach();
        }
        else {
            this->list.removeAt(static_cast<int>(index--));
        }
    }
        //std::thread(&Widget::do_work,this,std::ref(str)).detach();
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

    while (this->size.load() != this->list.size()) std::this_thread::yield();

//    boost::asio::thread_pool pool(8);
    
//    for(const auto & e : idVector)
//    {
//        boost::asio::post(pool, [this,&e](){this->do_work(e);} );
//    }
//    pool.join();

    this->tp2 = std::chrono::system_clock::now();
    const std::chrono::duration<double> diff = tp2 - tp;


    qDebug( (std::to_string( diff.count() ).c_str() ));

    this->FormTable();

    //this->FormLogFiles();
}

void Widget::FormTable() noexcept
{
    QStringList lst;
    for(std::int32_t index = 0; index < this->list.size(); ++ index)
        lst << QString::number(index)
            << QString("тайтл")<< QString("оценка")<< QString("серии")<< QString("время в минутах")<< QString("время в часах")
            << QString("время в сутках")<< QString("студия")<< QString("жанры");
    this->ptableWidget->setColumnCount(static_cast<int>(this->list.size()*9));
    this->ptableWidget->setHorizontalHeaderLabels(lst);
    for (std::int32_t index = 0; index < userInfoVector.size(); ++index )
    {
        QJsonArray json_array;
        userInfo info;
        for (std::int32_t inner_index = 0; inner_index < userInfoVector[index].titleInfo.size(); ++inner_index )
        {
            ++userInfoVector[index].studiosStats[userInfoVector[index].titleInfo[inner_index].studio].titles;
            userInfoVector[index].studiosStats[userInfoVector[index].titleInfo[inner_index].studio].episodes += userInfoVector[index].titleInfo[inner_index].episodes;
            bool b = 0;
            std::int32_t innerFoundIndex;
            for (std::int32_t index_ = 0; index_ < index; ++index_ )
            {
                for (std::int32_t inner_index_ = 0; inner_index_ < userInfoVector[index_].titleInfo.size(); ++inner_index_ )
                {
                    if(userInfoVector[index].titleInfo[inner_index].title == userInfoVector[index_].titleInfo[inner_index_].title)
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
                this->ptableWidget->insertRow(static_cast<int>((userInfoVector[index].titleInfo[inner_index].position = this->ptableWidget->rowCount() + 1 ) - 1));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(9*index + 1),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].title        ));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(9*index + 3),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes    )));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(9*index + 4),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes*20 )));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(9*index + 5),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/3. )));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(9*index + 6),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/72.)));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(9*index + 7),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].studio       ));
                QJsonObject obj;
                obj["title"] = userInfoVector[index].titleInfo[inner_index].title;
                obj["episodes"] = QString::number(userInfoVector[index].titleInfo[inner_index].episodes);
                json_array.push_back(obj);
            }
            else
            {
                userInfoVector[index].titleInfo[inner_index].position = innerFoundIndex;
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(9*index + 1),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].title        ));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(9*index + 3),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes    )));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(9*index + 4),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes*20 )));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(9*index + 5),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/3. )));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(9*index + 6),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/72.)));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(9*index + 7),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].studio       ));
                QJsonObject obj;
                obj["title"] = userInfoVector[index].titleInfo[inner_index].title;
                obj["episodes"] = QString::number(userInfoVector[index].titleInfo[inner_index].episodes);
                json_array.push_back(obj);
            }
            userInfoVector[index].episode += userInfoVector[index].titleInfo[inner_index].episodes;
        }

        QString filename = QDir::currentPath() + QString("/") + QDateTime::currentDateTime().toString("yyyy.MM.dd") + QString("_")
                                                + QDateTime::currentDateTime().toString("hh.mm.ss") + QString("_") + this->list[index] + QString(".json");
        QJsonDocument document;
        document.setArray(json_array);
        QByteArray json_data = document.toJson();
        QFile output(filename);
        if (output.open(QIODevice::WriteOnly | QIODevice::Text)){
            output.write(json_data);
            output.close();
        }
        else qDebug() << "Cannot open file";
        userInfoVector[index].titles_ = static_cast<std::int32_t>(userInfoVector[index].titleInfo.size());
        //this->userInfoVector.push_back(info);

    }
    //this->ptableWidget->setSortingEnabled(true);
    this->ptableWidget->insertRow(0);
    for (std::int32_t var = 0; var < this->userInfoVector.size(); ++var) {
        this->ptableWidget->setItem(0, static_cast<int>(9*var    ),new QTableWidgetItem( userInfoVector[var].nickname  ));
        this->ptableWidget->setItem(1, static_cast<int>(9*var    ),new QTableWidgetItem( userInfoVector[var].id  ));
        this->ptableWidget->setItem(0, static_cast<int>(9*var + 1),new QTableWidgetItem( QString("Всего: ") + this->userInfoVector[var].titles_ ));
        this->ptableWidget->setItem(0, static_cast<int>(9*var + 3),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode    )));
        this->ptableWidget->setItem(0, static_cast<int>(9*var + 4),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode*20 )));
        this->ptableWidget->setItem(0, static_cast<int>(9*var + 5),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode/3. )));
        this->ptableWidget->setItem(0, static_cast<int>(9*var + 6),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode/72.)));
    }
    //this->allTitles.erase(std::unique(this->allTitles.begin(),this->allTitles.end()),this->allTitles.end());
    //for (const auto & e : this->idVector) this->sortComboBox->addItem(QString::fromStdString( ("https://yummyanime.club/users/id" + e)  ));
}

void Widget::ShowStudioCharts() noexcept
{

    for(auto & e : this->userInfoVector){
        Form *pForm = new Form();
        pForm->provideData(&e.studiosStats, &e.genresStats, e.nickname);
        pForm->processData();
        pForm->show();
    }

    //




}

//void Widget::FormLogFiles() noexcept
//{
//    this->tp = std::chrono::system_clock::now();
//    boost::asio::thread_pool pool2(15);
//    for(std::int32_t index = 0; index < this->allUsersTitles.size() ; index++)
//    {
//        std::vector<std::pair<QString,std::pair<std::int32_t,std::int32_t>>> * a =&(allUsersTitles[index]);
//        boost::asio::post(pool2, [this, index, a]()
//        {
//            this->SaveFile(a, std::ref(idVector[index])) ;
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

//void Widget::SaveFile(  const std::vector<std::pair<QString,std::pair<std::int32_t,std::int32_t>>> * v ,  QString & str ) noexcept
//{
//    QString json_filter = "JSON (*.json)";
//    QDateTime current = QDateTime::currentDateTime();
//    QString filename = QString::fromStdString( current.toString("yyyy.MM.dd").toStdString() + " " + str);
//    //QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), "/", json_filter, &json_filter,QFileDialog::DontUseNativeDialog);
    
//    if(filename.isEmpty())
//    {
    
//    }
//    else 
//    {
        
//        QJsonDocument document;
//        QByteArray json_data = document.toJson();
//        QFile output(filename);
//        if( output.open(QIODevice::WriteOnly | QIODevice::Text)){
//            output.write(json_data);
//            output.close();
//            QMessageBox::information(this,tr("Succed"), tr("File Saved"));
//        } 
//        else 
//        {
//            QMessageBox::critical(this,tr("Error"), output.errorString());
//        }
        
//    }
    
    
//}


//void Widget::on_pushButton_2_clicked()
//{
//    QDesktopServices::openUrl(QUrl(QString::fromStdString((this->pidComboBoxList->currentText().toStdString()))));
//}

bool operator < ( const TitleInfo &first , const TitleInfo &second )
{
  return first.title < second.title;
}
