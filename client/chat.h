#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QTcpSocket>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <add.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <del.h>
#include <alter.h>
#include <QStandardItemModel>
#include<QAxObject>
#include <QTableView>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDate>
#include <QMessageBox>
namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QTcpSocket *c,QWidget *parent = 0);
    ~chat();
    bool static save(QString filePath,QStringList headers,QList<QStringList> data,QString comment="");
    //将QTableView保存为excel
    bool static saveFromTable(QString filePath,QTableView *tableView,QString comment="");
    bool static insert(QSqlQuery& query, QString sheetName, QStringList slist);


private slots:

    void readMessage();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::chat *ui;
    QDialog* add_dialog;
    QDialog* del_dialog;
    QStandardItemModel* standItemModel;
    QDialog* alter_dialog;
    QTcpSocket *client;
    QJsonArray array;
    void insert_table();
};

#endif // CHAT_H
