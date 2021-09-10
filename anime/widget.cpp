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
    
    std::atomic_init(&size, (uint32_t)0);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_work(const std::string &e) noexcept
{
    qDebug(((std::string("thread starts ") + e).c_str()));
    std::vector<Widget::TitleInfo> titles;
    Widget::userInfo userIdInfo;
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(std::string ("https://yummyanime.club/users/id" + e + "?tab=watched" ).c_str()));
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    const QByteArray arr = reply->readAll();
    std::string str = arr.toStdString();
    const std::string str_copy= str,sub_str;



    const std::size_t pos_start_nickname = str.find("Профиль ");

    const std::size_t pos_end_nickname = str.find("</title>", pos_start_nickname);
    userIdInfo.nickname = str.substr(pos_start_nickname + 14,pos_end_nickname - pos_start_nickname - 14);
    userIdInfo.id = e;



    //std::size_t pos_start_rate = str.find("fa fa-star");
    //pos_start_rate = str.find("class=\"fa fa-star\"", pos_start_rate);

    //std::string rate = str.substr(pos_start_rate,1000);
    //qDebug((rate.c_str()));
//    qDebug((std::to_string(pos_start_studio_2).c_str()));
//    qDebug((std::to_string(pos_end_studio).c_str()));
//    qDebug((std::to_string(pos_end_studio - pos_start_studio_2).c_str()));
//    qDebug((studio.c_str()));




    std::vector<std::size_t> vct;
    std::size_t pos_start = 0;
    while ( (pos_start = str.find("data-typeid=")) != std::string::npos){
        vct.push_back(pos_start + 16);
        str.erase ( str.begin() , str.begin() + 16 + pos_start);     //
    }
    std::size_t index = 0 ;
    std::vector <std::string> vct2;
    for (const auto & e : vct) {
        Q_UNUSED(e);
        std::size_t size_ = 0;
        for( std::size_t inner_index = 0 ; (inner_index <= index) && (index < vct.size()); ++inner_index){
            size_ += vct[inner_index];
        }
        ++index;
        if ((pos_start = str_copy.find("/", size_ )) != std::string::npos)
        {
            const std::size_t inner_size = str_copy.find("\"", pos_start);
            vct2.push_back( str_copy.substr( pos_start , inner_size - pos_start ));
        }
    }
    std::size_t _size = 0;
    for (const auto & e : vct2){
        
        const auto a = this->map.find(e);

        if (this->map.cend() != a){
                userIdInfo.titleInfo.push_back(a->second);
                continue;
        }
        //            std::string image_path = "";
        //            pos_start = str.find("<img src=\"/img/posters/");
        
        //            while ( isdigit(str[pos_start + 23]))
        //            {
        //                image_path += str[pos_start + 23];
        //                ++pos_start;
        
        //            }
        //            image_path = ("https://yummyanime.club/img/posters/" + image_path + ".jpg");
        //            qDebug() << image_path.c_str();

        QNetworkAccessManager manager;
        QNetworkRequest request(QUrl( (std::string("https://yummyanime.club") + e).c_str()));
        QNetworkReply *reply(manager.get(request));
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        const QByteArray arr = reply->readAll();
        const std::string str= arr.toStdString();
        const std::size_t pos_start_title = str.find("<h1>",0);
        const std::size_t end_start = str.find("</h1>",pos_start_title + 4);
        std::string sub_str = str.substr(pos_start_title + 4, end_start - pos_start_title);
        sub_str.erase(0, 8);
        std::size_t index=0;
        while(true)
        {
            if(index == sub_str.size()) break;
            if (sub_str[index] == sub_str[index + 1] ) 
            {
                sub_str.erase(index, sub_str.size() - index);
                break;
            }
            ++index;
        }
        const std::size_t pos_start_episodes = str.find("Серии:");
        std::string g;
        if (std::isdigit(str[pos_start_episodes + 21]))
        {
            g = "   ";
            g[1] = str[pos_start_episodes + 20];
            g[2] = str[pos_start_episodes + 21];
        }
        else if (std::isdigit(str[pos_start_episodes + 20]))
        {
            g = "  ";
            g[1] = str[pos_start_episodes + 20];
        }
        else g = " ";
        g[0] = str[pos_start_episodes + 19];
        _size  += std::atoi(g.c_str());


        std::size_t pos_start_studio = str.find("Студия:");
        pos_start_studio = str.find("<a href=\"/catalog/studio/", pos_start_studio);
        const std::size_t pos_end_studio = str.find("\">", pos_start_studio);
        std::string studio = "";
        if(std::string::npos != pos_end_studio){
            studio = str.substr(pos_start_studio + 25, pos_end_studio - pos_start_studio - 25);
        }
        this->map.insert( this->map.begin(),{e, {sub_str, studio,static_cast<std::size_t>(std::atoi(g.c_str())),0,0 }});



        userIdInfo.titleInfo.push_back({sub_str, studio,static_cast<std::size_t>(std::atoi(g.c_str())),0,0 });
    }
    this->mux.lock();
    this->userInfoVector.push_back(userIdInfo);
    this->size++;
    this->mux.unlock();
    qDebug(((std::string("thread ends") + e).c_str()));
}



void Widget::GetInput()
{
    std::regex re("[0-9]+");
    Dialog d(this);
    if(d.exec() == QDialog::Rejected) return;
    this->idVector.clear();
    this->ptableWidget->setRowCount(0);
    this->size.store(0);
    this->tp = std::chrono::system_clock::now();
    std::string text = (d.getText().toUtf8().constData() + std::string("\n"));
    qDebug(text.c_str());
    std::size_t pos;
    while ((pos = text.find('\n')) != std::string::npos) {
        const std::string token = text.substr(0, pos);
        text.erase(0, pos + 1);
        this->idVector.push_back(token);
    }

    for (std::size_t index = 0; index < idVector.size(); ++index){
        if(!std::regex_match(idVector[index],re)){
            idVector.erase(idVector.begin()+index--);
        }
    }
    //if ("" != text ) idVector.push_back(text);
    //std::sort(idVector.begin(),idVector.end());
    
    for(const auto & e : idVector)
    {
        //this->pidComboBoxList->addItem(QString::fromStdString("https://yummyanime.club/users/id" +e));
        std::thread(&Widget::do_work,this,std::ref(e)).detach();
        //auto a = std::async(&Widget::do_work, this, std::ref(e));
    }
    while (this->size.load() != this->idVector.size()) std::this_thread::yield();

//    boost::asio::thread_pool pool(8);
    
//    for(const auto & e : idVector)
//    {
//        boost::asio::post(pool, [this,&e](){this->do_work(e);} );
//    }
//    pool.join();
    this->FormTable();
    this->tp2 = std::chrono::system_clock::now();
    const std::chrono::duration<double> diff = tp2 - tp;


    qDebug( (std::to_string( diff.count() ).c_str() ));
    //this->FormLogFiles();
}

void Widget::FormTable() noexcept
{
    QStringList lst;
    for(std::size_t index = 0; index < this->idVector.size(); ++ index)
        lst << QString::fromStdString(std::to_string(index))
            << QString::fromStdString(std::string("тайтл"))
            << QString::fromStdString(std::string("оценка"))
            << QString::fromStdString(std::string("серии"))
            << QString::fromStdString(std::string("время в минутах"))
            << QString::fromStdString(std::string("время в часах"))
            << QString::fromStdString(std::string("время в сутках"))
            << QString::fromStdString(std::string("студия"))
            ;
    this->ptableWidget->setColumnCount(static_cast<int>(this->idVector.size()*8));
    this->ptableWidget->setHorizontalHeaderLabels(lst);
    for (std::size_t index = 0; index < userInfoVector.size(); ++index )
    {
        QJsonArray json_array;
        userInfo info;
        for (std::size_t inner_index = 0; inner_index < userInfoVector[index].titleInfo.size(); ++inner_index )
        {
            ++userInfoVector[index].studiosStats[userInfoVector[index].titleInfo[inner_index].studio];
            bool b = 0;
            std::size_t innerFoundIndex;
            for (std::size_t index_ = 0; index_ < index; ++index_ )
            {
                for (std::size_t inner_index_ = 0; inner_index_ < userInfoVector[index_].titleInfo.size(); ++inner_index_ )
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
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(8*index + 1),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].title.c_str()));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(8*index + 3),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes    )));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(8*index + 4),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes*20 )));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(8*index + 5),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/3. )));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(8*index + 6),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/72.)));
                this->ptableWidget->setItem  (static_cast<int>(this->ptableWidget->rowCount() - 1), static_cast<int>(8*index + 7),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].studio.c_str()));
                QJsonObject obj;
                obj["title"] = userInfoVector[index].titleInfo[inner_index].title.c_str() ;
                obj["episodes"] = QString::number(userInfoVector[index].titleInfo[inner_index].episodes);
                json_array.push_back(obj);
            }
            else
            {
                userInfoVector[index].titleInfo[inner_index].position = innerFoundIndex;
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(8*index + 1),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].title.c_str()));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(8*index + 3),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes    )));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(8*index + 4),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes*20 )));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(8*index + 5),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/3. )));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(8*index + 6),new QTableWidgetItem( QString::number( userInfoVector[index].titleInfo[inner_index].episodes/72.)));
                this->ptableWidget->setItem  (static_cast<int>(innerFoundIndex - 1), static_cast<int>(8*index + 7),new QTableWidgetItem(                  userInfoVector[index].titleInfo[inner_index].studio.c_str()));
                QJsonObject obj;
                obj["title"] = userInfoVector[index].titleInfo[inner_index].title.c_str() ;
                obj["episodes"] = QString::number(userInfoVector[index].titleInfo[inner_index].episodes);
                json_array.push_back(obj);
            }
            userInfoVector[index].episode += userInfoVector[index].titleInfo[inner_index].episodes;
        }
        QString filename = QString::fromStdString( QDateTime::currentDateTime().toString("yyyy.MM.dd").toStdString() + " " + QDateTime::currentDateTime().toString("hh:mm:ss").toStdString() +" " + idVector[index] + ".json");
        QJsonDocument document;
        document.setArray(json_array);
        QByteArray json_data = document.toJson();
        QFile output(filename);
        output.open(QIODevice::WriteOnly | QIODevice::Text);
        output.write(json_data);
        output.close();
        userInfoVector[index].titles_ = userInfoVector[index].titleInfo.size();
        //this->userInfoVector.push_back(info);

    }
    //this->ptableWidget->setSortingEnabled(true);
    this->ptableWidget->insertRow(0);
    for (std::size_t var = 0; var < this->userInfoVector.size(); ++var) {
        this->ptableWidget->setItem(0, static_cast<int>(8*var    ),new QTableWidgetItem( QString::fromStdString( userInfoVector[var].nickname  )));
        this->ptableWidget->setItem(1, static_cast<int>(8*var    ),new QTableWidgetItem( QString::fromStdString( userInfoVector[var].id  )));
        this->ptableWidget->setItem(0, static_cast<int>(8*var + 1),new QTableWidgetItem( QString::fromStdString( "Всего: " +std::to_string(this->userInfoVector[var].titles_) )));
        this->ptableWidget->setItem(0, static_cast<int>(8*var + 3),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode    )));
        this->ptableWidget->setItem(0, static_cast<int>(8*var + 4),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode*20 )));
        this->ptableWidget->setItem(0, static_cast<int>(8*var + 5),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode/3. )));
        this->ptableWidget->setItem(0, static_cast<int>(8*var + 6),new QTableWidgetItem( QString::number( this->userInfoVector[var].episode/72.)));
    }
    //this->allTitles.erase(std::unique(this->allTitles.begin(),this->allTitles.end()),this->allTitles.end());
    //for (const auto & e : this->idVector) this->sortComboBox->addItem(QString::fromStdString( ("https://yummyanime.club/users/id" + e)  ));
}

void Widget::ShowStudioCharts() noexcept
{

    for(auto & e : this->userInfoVector){
        Form *pForm = new Form();
        pForm->provideStudioData(&e.studiosStats, e.nickname);
        pForm->processStudioStats();
    }

    //pForm->show();




}

//void Widget::FormLogFiles() noexcept
//{
//    this->tp = std::chrono::system_clock::now();
//    boost::asio::thread_pool pool2(15);
//    for(std::size_t index = 0; index < this->allUsersTitles.size() ; index++)
//    {
//        std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> * a =&(allUsersTitles[index]);
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

//void Widget::SaveFile(  const std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> * v ,  std::string & str ) noexcept
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

bool operator < ( const Widget::TitleInfo &first , const Widget::TitleInfo &second )
{
  return first.title < second.title;
}
