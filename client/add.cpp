#include "add.h"
#include "ui_add.h"

Add::Add(QTcpSocket *c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    client=c;

}

Add::~Add()
{
    delete ui;
}

void Add::on_pushButton_clicked()
{//员工编号, 姓名,性别,加入公司日期,电话,员工级别,拥有假期时间,备注

    PersonData Data;
    QString str=ui->lineEdit->text();
    QByteArray ba=str.toLocal8Bit();
    Data.bianhao=ba.data();
    QString str1=ui->lineEdit_2->text();
    QByteArray ba1=str1.toLocal8Bit();
    Data.xinming=ba1.data();
    QString str2=ui->comboBox->currentText();
    QByteArray ba2=str2.toLocal8Bit();
    Data.xingbie=ba2.data();
    QString str3=ui->dateEdit->text();
   // QString str3=ui->lineEdit_3->text();
    QByteArray ba3=str3.toLocal8Bit();
    Data.jiarushijian=ba3.data();
    QString str4=ui->lineEdit_4->text();
    QByteArray ba4=str4.toLocal8Bit();
    Data.dianhua=ba4.data();
    QString str5 =ui->spinBox_2->text();
  //  QString str5=ui->lineEdit_5->text();
    QByteArray ba5=str5.toLocal8Bit();
    Data.jibie=ba5.data();
    QString str6=ui->spinBox->text();
    //QString str6=ui->lineEdit_6->text();
    QByteArray ba6=str6.toLocal8Bit();
    Data.jiaqishijian=ba6.data();
    QString str7=ui->lineEdit_7->text();
    QByteArray ba7=str7.toLocal8Bit();
    Data.beizhu=ba7.data();

     QString zstr="";
     zstr.append("1");
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
     zstr.append(",");
     zstr.append(str6);
     zstr.append(",");
     zstr.append(str5);
     zstr.append(",");
     zstr.append(str7);
     //qDebug()<<zstr;
     char * zs;
     QByteArray zba=zstr.toLocal8Bit();
     zs=zba.data();
     client->write(zs);
}
