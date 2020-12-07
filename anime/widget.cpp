#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    /*
    430622
    536964
    454905
    269705
    729512
    676306
    */
    std::size_t dialogReturnedValue = 0;
    Dialog d(this);
    dialogReturnedValue = d.exec();
    if(dialogReturnedValue == QDialog::Rejected) return;
    QString text2 = d.getText();
    std::string text = text2.toUtf8().constData();
    std::vector <std::string> idVector;
    std::size_t pos;
    while ((pos = text.find('\n')) != std::string::npos) {
    std::string token = text.substr(0, pos);
    text.erase(0, pos + 1);
    idVector.push_back(token);
  }
    if ("" != text ) idVector.push_back(text);
    std::vector<std::vector<std::pair<std::string,std::size_t>>> allUsersTitles;
    for(const auto & e : idVector)
    {
        std::vector <std::pair<std::string,std::size_t>> titles;
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
        for (auto & e : vct2){
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
                titles.push_back(std::make_pair(sub_str,std::atoi(g.c_str())));
            }
            else if (std::isdigit(str[pos_start + 20]))
            {
                std::string g = "  ";
                g[0] = str[pos_start + 19];
                g[1] = str[pos_start + 20];
                _size  += std::atoi(g.c_str());
                titles.push_back(std::make_pair(sub_str,std::atoi(g.c_str())));
            }
            else 
            {
                std::string g = " ";
                g[0] = str[pos_start + 19];
                _size  += std::atoi(g.c_str());
                titles.push_back(std::make_pair(sub_str,std::atoi(g.c_str())));
            }
        }
        allUsersTitles.push_back(titles);
    }
    QStringList lst;
    for(const auto & e: idVector) lst << QString::fromStdString(e) << QString::fromStdString(std::string("тайтл")) << QString::fromStdString(std::string("серии")) << QString::fromStdString(std::string("время в минутах")) << QString::fromStdString(std::string("время в часах")) << QString::fromStdString(std::string("время в сутках"));
    this->ui->tableWidget->setColumnCount(lst.size()*6);
    this->ui->tableWidget->setHorizontalHeaderLabels(lst);
    std::sort(allUsersTitles.begin(),allUsersTitles.end());
    for (std::size_t index = 0; index < allUsersTitles.size(); index++ )
    {
    userInfo info;
        for (std::size_t inner_index = 0; inner_index < allUsersTitles[index].size(); inner_index++ )
        {
            bool b = 0;
            std::size_t innerFoundIndex;
            for (std::size_t index_ = 0; index_ < index; index_++ )
            {
                for (std::size_t inner_index_ = 0; inner_index_ < allUsersTitles[index_].size(); inner_index_++ )
                {
                    if(allUsersTitles[index][inner_index] == allUsersTitles[index_][inner_index_]) 
                    {
                        b = true;
                        innerFoundIndex = inner_index_;
                        goto skip;
                    }
                }
            }
            skip:
            if(false == b)
            {
                this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 6*index + 1,new QTableWidgetItem( std::get<0>( allUsersTitles[index][inner_index] ).c_str()              ));
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 6*index + 2,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )    )));
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 6*index + 3,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )*20 )));
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 6*index + 4,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )/3. )));
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 6*index + 5,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )/72.)));
            }
            else
            {
                this->ui->tableWidget->setItem(innerFoundIndex, 6*index + 1,new QTableWidgetItem(                  std::get<0>( allUsersTitles[index][inner_index] ).c_str()));
                this->ui->tableWidget->setItem(innerFoundIndex, 6*index + 2,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )       )));
                this->ui->tableWidget->setItem(innerFoundIndex, 6*index + 3,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )*20    )));
                this->ui->tableWidget->setItem(innerFoundIndex, 6*index + 4,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )/3.    )));
                this->ui->tableWidget->setItem(innerFoundIndex, 6*index + 5,new QTableWidgetItem( QString::number( std::get<1>( allUsersTitles[index][inner_index] )/72.   )));
            }
            info.episode += std::get<1>( allUsersTitles[index][inner_index] );
            info.minuts  += std::get<1>( allUsersTitles[index][inner_index] )*20;
            info.hours   += std::get<1>( allUsersTitles[index][inner_index] )/3.;
            info.days    += std::get<1>( allUsersTitles[index][inner_index] )/72.;
        }
        this->userInfoVector.push_back(info);;
    }
    this->ui->tableWidget->setSortingEnabled(true);
    this->ui->tableWidget->insertRow(0);
    for (std::size_t var = 0; var < this->userInfoVector.size(); ++var) {
        //this->ui->tableWidget->setItem(0, 6*var + 0,new QTableWidgetItem( idVector[var].c_str() ));
        this->ui->tableWidget->setItem(0, 6*var + 2,new QTableWidgetItem( QString::number( this->userInfoVector[var].episode )));
        this->ui->tableWidget->setItem(0, 6*var + 3,new QTableWidgetItem( QString::number( this->userInfoVector[var].minuts  )));
        this->ui->tableWidget->setItem(0, 6*var + 4,new QTableWidgetItem( QString::number( this->userInfoVector[var].hours   )));
        this->ui->tableWidget->setItem(0, 6*var + 5,new QTableWidgetItem( QString::number( this->userInfoVector[var].days    )));
    }
}
