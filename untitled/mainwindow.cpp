#include "mainwindow.h"  
#include "ui_mainwindow.h"  
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::MainWindow)  
{  
    ui->setupUi(this);  

    socket = new QTcpSocket();  

    //连接信号槽  
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);  
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);  
  
    ui->pushButton_Send->setEnabled(false);  
    ui->lineEdit_IP->setText("101.132.131.164");
    ui->lineEdit_Port->setText("10774");
  
}  
  
MainWindow::~MainWindow()  
{  
    delete this->socket;  
    delete ui;  
}  
  
void MainWindow::on_pushButton_Connect_clicked()  
{  
    if(ui->pushButton_Connect->text() == "链接")
    {  
        qDebug() << "!!!";
        QString IP;  
        int port;  
  
        //获取IP地址  
        IP = ui->lineEdit_IP->text();  

        qDebug() << IP;
        //获取端口号  
        port = ui->lineEdit_Port->text().toInt();  
  
        //取消已有的连接  
        socket->abort();  
        //连接服务器  
        socket->connectToHost(IP, port);  
  
        //等待连接成功  
        if(!socket->waitForConnected(30000))
        {  
            qDebug() << "Connection failed!";  
            return;
        }
        qDebug() << "Connect successfully!";
        ui->pushButton_Send->setEnabled(true);
        ui->pushButton_Connect->setText("断开链接");
    }
    else
    {  
        //断开连接  
        socket->close();
        socket->disconnectFromHost();
        socket->waitForDisconnected();
        qDebug() << "Disconnected!2";
        //修改按键文字  
        ui->pushButton_Connect->setText("链接");
        ui->pushButton_Send->setEnabled(false);  
    }  
}  
  
void MainWindow::on_pushButton_Send_clicked()  
{  
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();  
    QString strtest = ui->textEdit_Send->toPlainText();
    QTextCodec *code= QTextCodec::codecForName("UTF-8");
    QByteArray bytest = code->fromUnicode( strtest );
    socket->write(bytest);
    socket->flush();  
}  
  
void MainWindow::socket_Read_Data()  
{  
    QByteArray buffer;  
    //读取缓冲区数据  
    buffer = socket->readAll();
    if(!buffer.isEmpty())  
    {
        QString str = ui->textEdit_Recv->toPlainText();
        str+=tr(buffer);  
        //刷新显示  
        ui->textEdit_Recv->setText(str);  
    }  
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->textEdit_Recv->toPlainText();
        str+=tr(buffer);
        //刷新显示
        ui->textEdit_Recv->setText(str);
    }
}  
  
void MainWindow::socket_Disconnected()  
{  
    //发送按键失能  
    ui->pushButton_Send->setEnabled(false);  
    //修改按键文字  
    ui->pushButton_Connect->setText("连接");  
    socket->close();
    socket->disconnectFromHost();
    socket->waitForDisconnected();
    qDebug() << "Disconnected!1";
}
