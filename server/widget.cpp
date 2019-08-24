#include "widget.h"
#include "ui_widget.h"
#include <QSqlRecord>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //setCentralWidget(Widget);
    server=new QTcpServer;
    server ->listen(QHostAddress::AnyIPv4,8888);

    connect(server,&QTcpServer::newConnection,this,&Widget::newCon);
    //连接数据库
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("employee");
    db.setUserName("root");
    db.setPassword("");
    db.open();

    setStyleSheet("QPushButton{background:yellow}QSlider{background:blue}");
            QPalette palette(this->palette());
            palette.setColor(QPalette::Background, Qt::blue);
            this->setPalette(palette);


            setWindowOpacity(0.95);


}


void Widget::newCon()
{
    socket=server->nextPendingConnection(); //创建socket连接

    QHostAddress clientAddress =socket->peerAddress();
    quint16 clientPort=socket->peerPort();

    ui->lineEdit->setText(clientAddress.toString());
    ui->lineEdit_2->setText(QString::number(clientPort));
    connect(socket,&QTcpSocket::readyRead,this,&Widget::dealData);
}

void Widget::tableToJson(){

    QSqlTableModel model(0,db);
    model.setTable("staff");

    model.select();
    int i=0;
    int j=0;
    QJsonArray js;
    for(i;i<model.rowCount();i++){
        QSqlRecord record= model.record(i);
        //qDebug()<<record;
        QJsonObject t;
        for(j;j<model.columnCount();j++){
            //qDebug()<<record.fieldName(j)<<record.value(j).toString();
            t.insert(record.fieldName(j),record.value(j).toString());

        }
        j=0;
        js.push_back(t);
    }
    //qDebug()<<js;
    QJsonDocument document=QJsonDocument(js);
    QByteArray by=document.toJson();
    socket->write(by);
}

void Widget::dealData()
{
    QString str;
    QByteArray data = socket->readAll();
    data.resize(1024);
    str=data.data();
    //qDebug()<<str;
    QString str1=str.section(',', 0, 0).trimmed().toUtf8();
    //qDebug()<<str1;
    QString str2=str.section(',', 1, 1).trimmed().toUtf8();
    //qDebug()<<str2;
    QString str3=str.section(',', 2, 2).trimmed().toUtf8();
    //qDebug()<<str3;
    QString str4=str.section(',', 3, 3).trimmed().toUtf8();
    //qDebug()<<str4;
    QString str5=str.section(',', 4, 4).trimmed().toUtf8();
    //qDebug()<<str5;
    QString str6=str.section(',', 5, 5).trimmed().toUtf8();
    //qDebug()<<str6;
    QString str7=str.section(',', 6, 6).trimmed().toUtf8();
    //qDebug()<<str7;
    QString str8=str.section(',', 7, 7).trimmed().toUtf8();
    //qDebug()<<str8;
    QString str9=str.section(',', 8, 8).trimmed().toUtf8();
    //qDebug()<<str9;
    if(str1=="1"){
        qDebug()<<"add";
        QSqlQuery query;
        QString str = QString("insert into staff values('%1', '%2', '%3' ,'%4' ,'%5' ,'%6','%7','%8')").arg(str2).arg(str3).arg(str4).
                    arg(str5).arg(str6).arg(str7).arg(str8).arg(str9);
            if(query.exec(str))
            {
                ui->textEdit->insertPlainText("\n入职成功!!!\n");
            }
            else
            {
                ui->textEdit->insertPlainText("\n入职失败!!!\n");
            }
    }
    else if(str1=="2"){
        qDebug()<<"del";
        QSqlQuery query;
        QString str = QString("delete from staff where 员工编号='%1'").arg(str2);
            if(query.exec(str))
            {
                ui->textEdit->insertPlainText("\n删除成功!!!\n");
            }
            else
            {
                ui->textEdit->insertPlainText("\n删除失败!!!\n");
            }
    }
    else if(str1=="3"){
        qDebug()<<"alter";
        QSqlQuery query;
        QString str = QString("update staff set 电话='%1',员工级别='%2',拥有假期时间='%3',备注='%4' where 姓名='%5'").arg(str3).arg(str4).arg(str5).arg(str6).arg(str2);
            if(query.exec(str))
            {
                ui->textEdit->insertPlainText("\n修改成功!!!\n");
            }
            else
            {
                ui->textEdit->insertPlainText("\n修改失败!!!\n");
            }
    }
    else if(str1=="4"){
        qDebug()<<"select";
        QSqlQuery query;
        QString str = QString("select * from staff where 姓名='%1'").arg(str2);
            if(query.exec(str))
            {
                ui->textEdit->insertPlainText("\n查询成功!!!\n");
                query.next();
                QSqlRecord s=query.record();
                qDebug()<<query.value(0).toString()<<query.value(1).toString();
                QJsonArray js;
                QJsonObject t;
                //t.insert(s.field(0),s.value(0).toString());
                t.insert("员工编号",s.value(0).toString());
                t.insert("姓名",s.value(1).toString());
                t.insert("性别",s.value(2).toString());
                t.insert("加入公司日期",s.value(3).toString());
                t.insert("电话",s.value(4).toString());
                t.insert("员工级别",s.value(5).toString());
                t.insert("拥有假期时间",s.value(6).toString());
                t.insert("备注",s.value(7).toString());

                js.push_back(t);

            //qDebug()<<js;
            QJsonDocument document=QJsonDocument(js);
            QByteArray by=document.toJson();
            socket->write(by);
            }
            else
            {
                ui->textEdit->insertPlainText("\n查询失败!!!\n");
            }


    }
    else if(str1=="5"){
        qDebug()<<"select all";
        ui->textEdit->insertPlainText("\n查询成功!!!\n");
        tableToJson();
    }
}

Widget::~Widget()
{
    delete ui;
}
