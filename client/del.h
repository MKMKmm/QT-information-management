#ifndef DEL_H
#define DEL_H

#include <QDialog>
#include <QTcpSocket>
namespace Ui {
class Del;
}

class Del : public QDialog
{
    Q_OBJECT

public:
    explicit Del(QTcpSocket *c,QWidget *parent = nullptr);
    ~Del();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Del *ui;
    QTcpSocket* client;
};

#endif // DEL_H
