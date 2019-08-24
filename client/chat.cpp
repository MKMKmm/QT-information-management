#include "chat.h"
#include "ui_chat.h"
#include <QString>
#include <QFile>
chat::chat(QTcpSocket *c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    this->client=c;
    ui->setupUi(this);
    client=c;
    connect(client, &QTcpSocket::readyRead, this, &chat::readMessage);
    standItemModel = new QStandardItemModel();
    standItemModel->setColumnCount(8);
    standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("员工编号"));   //设置表头内容
    standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("姓名"));
    standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("性别"));
    standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("加入公司日期"));   //设置表头内容
    standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("电话"));
    standItemModel->setHeaderData(5,Qt::Horizontal,QStringLiteral("员工级别"));
    standItemModel->setHeaderData(6,Qt::Horizontal,QStringLiteral("假期时间"));   //设置表头内容
    standItemModel->setHeaderData(7,Qt::Horizontal,QStringLiteral("备注"));
    ui->tableView->setModel(standItemModel);



}

chat::~chat()
{
    delete ui;
}


void chat::on_pushButton_2_clicked()
{
    this->close();
}

void chat::on_pushButton_3_clicked()
{
     QString str=ui->lineEdit->text();
     QString zstr="";
     zstr.append("4");
     zstr.append(",");
     zstr.append(str);
     //qDebug()<<zstr;
     char * zs;
     QByteArray zba=zstr.toLocal8Bit();
     zs=zba.data();
     client->write(zs);
}
void chat::readMessage(){
    QByteArray data = client->readAll();
    //qDebug()<<data.data();
    QJsonDocument document2=QJsonDocument::fromJson(data.data());
    array = document2.array();
    //qDebug()<<array;
    insert_table();
}
void chat::insert_table(){
    int i=0;
    standItemModel->removeRows(0,standItemModel->rowCount());
    while(!(array.isEmpty())){
        QJsonValue t=array.takeAt(0);
        QString item1=t["员工编号"].toString();
        QString item2=t["姓名"].toString();
        QString item3=t["性别"].toString();
        QString item4=t["加入公司日期"].toString();
        QString item5=t["电话"].toString();
        QString item6=t["员工级别"].toString();
        QString item7=t["拥有假期时间"].toString();
        QString item8=t["备注"].toString();

        //qDebug()<<item1<<","<<item2<<","<<item3<<","<<item4<<","<<item5<<","<<item6<<","<<item7<<","<<item8;
        standItemModel->setItem(i,0,new QStandardItem(item1));
        standItemModel->setItem(i,1,new QStandardItem(item2));
        standItemModel->setItem(i,2,new QStandardItem(item3));
        standItemModel->setItem(i,3,new QStandardItem(item4));
        standItemModel->setItem(i,4,new QStandardItem(item5));
        standItemModel->setItem(i,5,new QStandardItem(item6));
        standItemModel->setItem(i,6,new QStandardItem(item7));
        standItemModel->setItem(i,7,new QStandardItem(item8));
        //standItemModel->setItem(i,0,t["员工编号"].toString());
        //standItemModel->setItem(i,1,t["姓名"].toString());
        i++;
    }

    /*for(int i=0;i<100;i++)
       {
           QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(i+1));
           QStandardItem *standItem2 = new QStandardItem(tr("第%1行").arg(i+1));
           standItemModel->setItem(i,0,standItem1);                                //表格第i行，第0列添加一项内容
           standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
           standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
           standItemModel->setItem(i,1,standItem2);                                //表格第i行，第1列添加一项内容
       }*/
}
void chat::on_pushButton_4_clicked()
{
    add_dialog=new Add(client,this);
    add_dialog->setModal(false);
    add_dialog->show();
}

void chat::on_pushButton_5_clicked()
{
    del_dialog=new Del(client,this);
    del_dialog->setModal(false);
    del_dialog->show();
}

void chat::on_pushButton_6_clicked()
{
    alter_dialog=new Alter(client,this);
    alter_dialog->setModal(false);
    alter_dialog->show();
}

void chat::on_pushButton_clicked()
{
    QString zstr="";
    zstr.append("5");

    //qDebug()<<zstr;
    char * zs;
    QByteArray zba=zstr.toLocal8Bit();
    zs=zba.data();
    client->write(zs);
}
bool chat::saveFromTable(QString filePath, QTableView *tableView, QString comment)
{
    QAbstractItemModel *model=tableView->model();
    const int column=model->columnCount();
    const int row=model->rowCount();

    //header
    QStringList headers;
    for(int i=0;i<column;i++)
    {
        //隐藏列
        if(tableView->isColumnHidden(i))
            continue;
        headers<<model->headerData(i,Qt::Horizontal).toString();
    }

    //data
    QStringList list;
    QList<QStringList> data;
    for(int i=0;i<row;i++)
    {
        if(model->index(i,0).data().isNull())
            continue;
        list.clear();
        for(int j=0;j<column;j++){
            //隐藏列
            if(tableView->isColumnHidden(j))
                continue;
            list<<model->index(i,j).data().toString();
        }
        data<<list;
    }
    return chat::save(filePath,headers,data,comment);
}
bool chat::save(QString filePath, QStringList headers, QList<QStringList> data,QString comment)
{
    QString sheetName = "Sheet1";

    // 创建一个数据库实例， 设置连接字符串
    QSqlDatabase dbexcel = QSqlDatabase::addDatabase("QODBC","excelexport");
    if(!dbexcel.isValid())
    {
        qDebug()<<"数据库驱动异常";
        return false;   //! type error
    }

    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").
                  arg(filePath).arg(filePath);
    qDebug()<<dsn;
    dbexcel.setDatabaseName(dsn);

    // open connection
    if(!dbexcel.open())
    {
         qDebug()<<"无法打开数据库";
        return false;  //! db error
    }

    QSqlQuery query(dbexcel);
    QString sql;

    // drop the table if it's already exists
    sql = QString("DROP TABLE [%1]").arg(sheetName);
    query.exec( sql);
    //create the table (sheet in Excel file)
    sql = QString("CREATE TABLE [%1] (").arg(sheetName);
    foreach (QString name, headers) {
        sql +=QString("[%1] varchar(200)").arg(name);
        if(name!=headers.last())
            sql +=",";
    }
    sql += ")";
    query.prepare(sql);
    if( !query.exec()) {
        //UIDemo01::printError( query.lastError());
        dbexcel.close();
        return false;
    }
    foreach (QStringList slist, data) {
        insert(query,sheetName,slist);
    }
    if(!comment.isEmpty())
    {
        QStringList slist;
        slist<<comment;
        for(int i=0,n=headers.size()-1;i<n;i++)
        {
            slist<<"";
        }
        insert(query,sheetName,slist);
    }

    dbexcel.close();
    return true;
}
bool chat::insert(QSqlQuery &query, QString sheetName, QStringList slist)
{
    QString sSql = QString("INSERT INTO [%1] VALUES(").arg(sheetName);
    for(int i=0,n=slist.size();i<n;i++)
    {
        sSql+=QString(":%1").arg(i);
        if(i!=n-1)
            sSql+=",";
        else
            sSql+=")";
    }
    query.prepare(sSql);
    for(int i=0,n=slist.size();i<n;i++)
    {
        query.bindValue(QString(":%1").arg(i),slist.at(i));
    }
    if( !query.exec()) {

        return false;
    }
    return true;
}
void chat::on_pushButton_7_clicked()
{
    QFileDialog dlg;
    QString filename;
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    dlg.setNameFilter("*.xls");
    filename=QDate::currentDate().toString("yyyy-MM-dd")+"body.xls";
    dlg.selectFile(filename);
    if(dlg.exec()!= QDialog::Accepted)
        return;
    QString filePath=dlg.selectedFiles()[0];//得到用户选择的文件名
    //qDebug()<<filePath;
    if(chat::saveFromTable(filePath,ui->tableView)) {
        QMessageBox::information(this,tr("提示"),tr("保存成功"));
    }
    else{
        QMessageBox::information(this,tr("提示"),tr("保存失败"));
    }
}

void chat::on_comboBox_activated(const QString &arg1)
{
    QString str;
       str=ui->comboBox->currentText();
       if(str=="皮肤一")
          {
           QFile file("./1.qss");
           file.open(QFile::ReadOnly);
          QString styleSheet = tr(file.readAll());
          qApp->setStyleSheet(styleSheet);
       }
       if(str=="皮肤二")
       {
        QFile file("./2.qss");
        file.open(QFile::ReadOnly);
       QString styleSheet = tr(file.readAll());
       qApp->setStyleSheet(styleSheet);
    }

}
