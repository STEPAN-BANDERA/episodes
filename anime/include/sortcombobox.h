#ifndef SORTCOMBOBOX_H
#define SORTCOMBOBOX_H

#include <QComboBox>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>
class SortComboBox : public QComboBox
{
    Q_OBJECT
public:
    SortComboBox();

protected:
//    virtual void mousePressEvent(QMouseEvent *event) override;
private slots:
     void open_link();
     
     // QWidget interface
protected:
     virtual void changeEvent(QEvent *) override;
};

#endif // SORTCOMBOBOX_H
