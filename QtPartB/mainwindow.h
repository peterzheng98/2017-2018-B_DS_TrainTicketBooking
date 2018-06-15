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

    void on_tab4_logined_frame_modifyinfo_clicked();

    void on_tab4_logined_frame_modifyprivilege_clicked();

    void tab1_reset();

    void tab2_reset();

    void tab3_reset();

    void tab4_reset();

    void tab5_reset();

    void work(QString str);

    void on_tab4_logined_frame_search_clicked();

    void on_tab2_ticketShowing_clicked(const QModelIndex &index);

    void on_tab2_cata_currentIndexChanged(int index);

    void on_tab3_logined_frame_search_clicked();

    void on_tab3_ticketHistory_clicked(const QModelIndex &index);

    void on_group_refund_button_clicked();

    void on_tab2_booking_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
