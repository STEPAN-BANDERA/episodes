#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->ui->setupUi(this);
    this->allTitles.reserve(1000);
    this->allUsersTitles.reserve(10);
    this->ptableWidget = new QTableWidget;

    this->sortComboBox = new SortComboBox;
    this->pidComboBoxList = new QComboBox;

    this->pcallOpenLink  = new QPushButton("Open choosed profile");
    this->pcallDialogWindow = new QPushButton("Gеt input ids");
    this->pOpenJsonFile = new QPushButton("Add Data From File");
    

    this->pHorizontalbxLayout = new QHBoxLayout;
    this->pVerticallbxLayout = new QVBoxLayout;
    this->pHorizontalbxLayout->addWidget(this->sortComboBox, 3);

    this->pHorizontalbxLayout->addWidget(this->pidComboBoxList, 3);
    this->pHorizontalbxLayout->addWidget(this->pcallOpenLink, 2);
    this->pHorizontalbxLayout->addWidget(this->pcallDialogWindow, 2);
    this->pHorizontalbxLayout->addWidget(this->pOpenJsonFile, 2);
    this->pVerticallbxLayout ->addWidget(this->ptableWidget);
    this->pVerticallbxLayout ->addLayout(this->pHorizontalbxLayout); 
    this->setWindowTitle("Check profile");

    this->setLayout(this->pVerticallbxLayout);
    
    connect(pcallDialogWindow, SIGNAL (released()),this, SLOT (  GetInput()));
    //connect(pcallOpenLink,     SIGNAL (released()),this, SLOT (on_pushButton_2_clicked()));
    connect(pOpenJsonFile,     SIGNAL (released()),this, SLOT (  OpenFile()));
    
    std::atomic_init(&size, 0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_work(const std::string &e) noexcept
{
        std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> titles;
        QNetworkAccessManager manager;
        QNetworkRequest request(QUrl(std::string ("https://yummyanime.club/users/id" + e + "?tab=watched" ).c_str()));
        QNetworkReply *reply(manager.get(request));
        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        QByteArray arr = reply->readAll();
        std::string str = arr.toStdString();
        std::string str_copy= str,sub_str;
        std::vector<std::size_t> vct;
        std::size_t pos_start = 0;
        while ( (pos_start = str.find("data-typeid=")) != std::string::npos){
            vct.push_back(pos_start + 16);
            str.erase ( str.begin() , str.begin() + 16 + pos_start);     // get from "live" to the end
        }
        std::size_t index = 0 ;
        std::vector <std::string> vct2;
        for (const auto & e : vct) {
            std::size_t size_ = 0;
            for( std::size_t inner_index = 0 ; (inner_index <= index) && (index < vct.size()); ++inner_index){
                size_ += vct[inner_index];
            }
            ++index;
            if ((pos_start = str_copy.find("/", size_ )) != std::string::npos)
            {
                std::size_t inner_size = str_copy.find("\"", pos_start);
                vct2.push_back( str_copy.substr( pos_start , inner_size - pos_start ));
            }
        }
        std::size_t _size = 0;
        for (const auto & e : vct2){
            QNetworkAccessManager manager;
            QNetworkRequest request(QUrl( (std::string("https://yummyanime.club") + e).c_str()));
            QNetworkReply *reply(manager.get(request));
            QEventLoop loop;
            QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            QByteArray arr = reply->readAll();
            std::string str;
            str.reserve(200000);
            str = arr.toStdString();
            std::size_t pos_start2 = str.find("<h1>",0);
            std::size_t end_start = str.find("</h1>",pos_start2 + 4);
            std::string sub_str = str.substr(pos_start2 + 4, end_start - pos_start2);
            sub_str.erase(0, 20);
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
            std::size_t pos_start = str.find("Серии:");
            if (std::isdigit(str[pos_start + 21]))
            {
                std::string g = "   ";
                g[0] = str[pos_start + 19];
                g[1] = str[pos_start + 20];
                g[2] = str[pos_start + 21];
                _size  += std::atoi(g.c_str());
                titles.push_back(std::make_pair(sub_str,std::make_pair(std::atoi(g.c_str()),0)));
            }
            else if (std::isdigit(str[pos_start + 20]))
            {
                std::string g = "  ";
                g[0] = str[pos_start + 19];
                g[1] = str[pos_start + 20];
                _size  += std::atoi(g.c_str());
                titles.push_back(std::make_pair(sub_str,std::make_pair(std::atoi(g.c_str()),0)));
            }
            else 
            {
                std::string g = " ";
                g[0] = str[pos_start + 19];
                _size  += std::atoi(g.c_str());
                titles.push_back(std::make_pair(sub_str,std::make_pair(std::atoi(g.c_str()),0)));
            }
        }
        this->mux.lock();
        this->allUsersTitles.push_back(titles);
        this->size++;
        qDebug("thread ends");
        this->mux.unlock();
        
}

void Widget::GetInput()
{
    std::size_t dialogReturnedValue = 0;
    Dialog d(this);
    dialogReturnedValue = d.exec();
    auto tp = std::chrono::system_clock::now();
    if(dialogReturnedValue == QDialog::Rejected) return;
    QString text2 = d.getText();
    qDebug((text2.toStdString()).c_str());
    std::string text = text2.toUtf8().constData();
    this->idVector;
    std::size_t pos;
    while ((pos = text.find('\n')) != std::string::npos) {
        std::string token = text.substr(0, pos);
        text.erase(0, pos + 1);
        this->idVector.push_back(token);
    }
    if ("" != text ) this->idVector.push_back(text);
   
    //for(const auto & e : idVector)
    //{
        //this->pidComboBoxList->addItem(QString::fromStdString("https://yummyanime.club/users/id" +e));
        //std::thread(&Widget::do_work,this,std::ref(e)).detach();
        //auto a = std::async(&Widget::do_work, this, std::ref(e));
    //}
    
    boost::asio::thread_pool pool(15);
    
    for(const auto & e : idVector)
    {
        boost::asio::post(pool, [this,&e](){this->do_work(e);} );
    }
    pool.join();
    
    while (this->size.load() != this->idVector.size()) std::this_thread::yield();
    
    
    
    QStringList lst;
    for(const auto & e: this->idVector) lst << QString::fromStdString(e) << QString::fromStdString(std::string("тайтл")) << QString::fromStdString(std::string("серии")) << QString::fromStdString(std::string("время в минутах")) << QString::fromStdString(std::string("время в часах")) << QString::fromStdString(std::string("время в сутках"));
    this->ptableWidget->setColumnCount(this->idVector.size()*6);
    this->ptableWidget->setHorizontalHeaderLabels(lst);
    //std::sort(allUsersTitles.begin(),allUsersTitles.end());
    
    for (std::size_t index = 0; index < allUsersTitles.size(); index++ )
    {
    userInfo info;
        for (std::size_t inner_index = 0; inner_index < allUsersTitles[index].size(); inner_index++ )
        {
            this->allTitles.push_back(std::get<0>(allUsersTitles[index][inner_index] ));
            bool b = 0;
            std::size_t innerFoundIndex;
            for (std::size_t index_ = 0; index_ < index; index_++ )
            {
                for (std::size_t inner_index_ = 0; inner_index_ < allUsersTitles[index_].size(); inner_index_++ )
                {
                    if( std::get<0>(allUsersTitles[index][inner_index]) == std::get<0>(allUsersTitles[index_][inner_index_])) 
                    {
                        b = true;
                        innerFoundIndex = std::get<1>(std::get<1>(allUsersTitles[index_][inner_index_]));
                        goto skip;
                    }
                }
            }
            skip:
            if(false == b)
            {
                this->ptableWidget->insertRow(this->ptableWidget->rowCount());
                this->ptableWidget->setItem  (this->ptableWidget->rowCount() - 1, 6*index + 1,new QTableWidgetItem(                               std::get<0>(allUsersTitles[index][inner_index] ).c_str()));
                this->ptableWidget->setItem  (this->ptableWidget->rowCount() - 1, 6*index + 2,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))      )));
                this->ptableWidget->setItem  (this->ptableWidget->rowCount() - 1, 6*index + 3,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))*20   )));
                this->ptableWidget->setItem  (this->ptableWidget->rowCount() - 1, 6*index + 4,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))/3.   )));
                this->ptableWidget->setItem  (this->ptableWidget->rowCount() - 1, 6*index + 5,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))/72.  )));
                std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) = this->ptableWidget->rowCount();
            }
            else
            {
                std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) = innerFoundIndex;
                this->ptableWidget->setItem(std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) - 1, 6*index + 1,new QTableWidgetItem(                               std::get<0>(allUsersTitles[index][inner_index] ).c_str()));
                this->ptableWidget->setItem(std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) - 1, 6*index + 2,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))      )));
                this->ptableWidget->setItem(std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) - 1, 6*index + 3,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))*20   )));
                this->ptableWidget->setItem(std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) - 1, 6*index + 4,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))/3.   )));
                this->ptableWidget->setItem(std::get<1>( std::get<1>(allUsersTitles[index][inner_index] )) - 1, 6*index + 5,new QTableWidgetItem( QString::number( std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))/72.  )));
            }
            info.episode += std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ));
            info.minuts  += std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))*20;
            info.hours   += std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))/3.;
            info.days    += std::get<0>( std::get<1>(allUsersTitles[index][inner_index] ))/72.;
        }
        info.titles_ = allUsersTitles[index].size();
        this->userInfoVector.push_back(info);
    }
    //this->ptableWidget->setSortingEnabled(true);
    this->ptableWidget->insertRow(0);
    for (std::size_t var = 0; var < this->userInfoVector.size(); ++var) {
        this->ptableWidget->setItem(0, 6*var + 1,new QTableWidgetItem( QString::fromStdString( "Всего: " +std::to_string(this->userInfoVector[var].titles_) )));
        this->ptableWidget->setItem(0, 6*var + 2,new QTableWidgetItem( QString::number( this->userInfoVector[var].episode )));
        this->ptableWidget->setItem(0, 6*var + 3,new QTableWidgetItem( QString::number( this->userInfoVector[var].minuts  )));
        this->ptableWidget->setItem(0, 6*var + 4,new QTableWidgetItem( QString::number( this->userInfoVector[var].hours   )));
        this->ptableWidget->setItem(0, 6*var + 5,new QTableWidgetItem( QString::number( this->userInfoVector[var].days    )));
    }
    auto tp2 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = tp2 - tp;
    qDebug( (std::to_string( diff.count() ).c_str() ));
    tp = std::chrono::system_clock::now();
    boost::asio::thread_pool pool2(15);
    for(std::size_t index = 0; index < this->allUsersTitles.size() ; index++)
    {
        std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> * a =&(allUsersTitles[index]);
        boost::asio::post(pool2, [this, index, a]()
        {
            this->SaveFile(a, std::ref(idVector[index])) ;
        } );
    }
    pool2.join();
    while (this->size.load() != this->idVector.size()) std::this_thread::yield();
    tp2 = std::chrono::system_clock::now();
    diff = tp2 - tp;
    qDebug( (std::to_string( diff.count() ).c_str() ));
    
    //this->allTitles.erase(std::unique(this->allTitles.begin(),this->allTitles.end()),this->allTitles.end());
    //for (const auto & e : this->idVector) this->sortComboBox->addItem(QString::fromStdString( ("https://yummyanime.club/users/id" + e)  ));
    
}

void Widget::OpenFile()
{
    QString json_filter = "JSON (*.json)";
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), "/", json_filter, &json_filter,QFileDialog::DontUseNativeDialog);
    
    if(filename.isEmpty())
    {
    
    }
    else 
    {
    
    }
    
    
}

void Widget::SaveFile(  const std::vector<std::pair<std::string,std::pair<std::size_t,std::size_t>>> * v ,  std::string & str )
{
    QString json_filter = "JSON (*.json)";
    QDateTime current = QDateTime::currentDateTime();
    QString filename = QString::fromStdString( current.toString("yyyy.MM.dd").toStdString() + " " + str);
    //QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), "/", json_filter, &json_filter,QFileDialog::DontUseNativeDialog);
    
    if(filename.isEmpty())
    {
    
    }
    else 
    {
        QJsonDocument document;
        QByteArray json_data = document.toJson();
        QFile output(filename);
        if( output.open(QIODevice::WriteOnly | QIODevice::Text)){
            output.write(json_data);
            output.close();
            QMessageBox::information(this,tr("Succed"), tr("File Saved"));
        } 
        else 
        {
            QMessageBox::critical(this,tr("Error"), output.errorString());
        }
        
    }
    
    
}

//void Widget::on_pushButton_2_clicked()
//{
//    QDesktopServices::openUrl(QUrl(QString::fromStdString((this->pidComboBoxList->currentText().toStdString()))));
//}
