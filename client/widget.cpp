#include "widget.h"
#include "ui_widget.h"
#include "chat.h"

Widget::Widget(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    client =new QTcpSocket;

        connect(client,&QTcpSocket::connected,
                [this]()
        {
            QMessageBox::information(this,"连接提示","连接成功");
            this->close();
            chat *c=new chat(client);
            c->show();
        });
        setStyleSheet("QPushButton{background:yellow}QSlider{background:blue}");
                QPalette palette(this->palette());
                palette.setColor(QPalette::Background, Qt::blue);
                this->setPalette(palette);

                //setWindowOpacity(0.4);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QHostAddress serverAddress(ui->lineEdit->text());
    quint16 serverPort=ui->lineEdit_2->text().toShort();

    client->connectToHost(serverAddress,serverPort);

}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}
