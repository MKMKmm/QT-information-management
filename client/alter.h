#ifndef ALTER_H
#define ALTER_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class Alter;
}

class Alter : public QDialog
{
    Q_OBJECT

public:
    explicit Alter(QTcpSocket *c,QWidget *parent = nullptr);
    ~Alter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Alter *ui;
    QTcpSocket *client;
};

#endif // ALTER_H
