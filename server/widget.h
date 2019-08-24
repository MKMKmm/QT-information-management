#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlRecord>
namespace Ui {
class Widget;
}

struct PersonData{
    char * bianhao;
    char * xinming;
    char * xingbie;
    char * jiarushijian;
    char * dianhua;
    char * jibie;
    char * jiaqishijian;
    char * beizhu;

};
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void tableToJson();
    ~Widget();
public slots:
    void newCon();
    void dealData();
private:
    Ui::Widget *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QSqlDatabase db;
    QSqlTableModel* model;
};

#endif // WIDGET_H
