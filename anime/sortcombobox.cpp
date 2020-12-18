#include "sortcombobox.h"

SortComboBox::SortComboBox()
{
    QObject::connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(open_link()));
}


//void SortComboBox::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);

//}

void SortComboBox::open_link()
{
    QDesktopServices::openUrl(QUrl(QString::fromStdString((this->currentText().toStdString()))));
}


void SortComboBox::changeEvent(QEvent *)
{
}
