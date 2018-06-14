#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QString>
#include<QString>
#include<QDataStream>
#include<QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_login_frame_login_clicked();

    void on_pushButton_clicked();

    void on_user_frame_logout_clicked();

    void on_login_frame_reset_clicked();

    void on_tab5_nologin_frame_register_clicked();

    void on_tab4_logined_frame_usercheckid_clicked();

    void socket_Read_Data();

    void socket_Disconnected();

    QString get(QString str);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
