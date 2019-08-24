#include "del.h"
#include "ui_del.h"

Del::Del(QTcpSocket* c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Del)
{
    ui->setupUi(this);
    client=c;
}

Del::~Del()
{
    delete ui;
}

void Del::on_pushButton_clicked()
{

    QString str=ui->lineEdit->text();
    QByteArray ba=str.toLocal8Bit();
    QString zstr="";
    zstr.append("2");
    zstr.append(",");
    zstr.append(str);
     //qDebug()<<zstr;
     char * zs;
     QByteArray zba=zstr.toLocal8Bit();
     zs=zba.data();
     client->write(zs);
}
