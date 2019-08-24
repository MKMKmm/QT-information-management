#include "alter.h"
#include "ui_alter.h"

Alter::Alter(QTcpSocket *c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alter)
{
    ui->setupUi(this);
    client=c;
}

Alter::~Alter()
{
    delete ui;
}

void Alter::on_pushButton_clicked()
{

    QString str=ui->lineEdit->text();
    QString str1=ui->lineEdit_2->text();
    QString str2=ui->lineEdit_3->text();
    QString str3=ui->lineEdit_4->text();
    QString str4=ui->lineEdit_5->text();

     QString zstr="";
     zstr.append("3");
     zstr.append(",");
     zstr.append(str);
     zstr.append(",");
     zstr.append(str1);
     zstr.append(",");
     zstr.append(str2);
     zstr.append(",");
     zstr.append(str3);
     zstr.append(",");
     zstr.append(str4);
     //qDebug()<<zstr;
     char * zs;
     QByteArray zba=zstr.toLocal8Bit();
     zs=zba.data();
     client->write(zs);
}
