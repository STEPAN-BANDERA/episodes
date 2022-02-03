#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->ui->textEdit->setText("269705\n729512\n430622\n676306\n771703\n486214\n536964\n454905\n701345\n996152");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

QString Dialog::getText() const
{
    return this->ui->textEdit->toPlainText();
}
