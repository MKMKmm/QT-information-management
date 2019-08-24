#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QTcpSocket>
namespace Ui {
class Add;
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
class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QTcpSocket *c,QWidget *parent = nullptr);
    ~Add();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Add *ui;
    QTcpSocket *client;
};

#endif // ADD_H
