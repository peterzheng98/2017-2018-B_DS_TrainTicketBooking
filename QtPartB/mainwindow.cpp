#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStringListModel>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->userFrame->setVisible(false);

    ui->tab1_nologin->setVisible(true);
    ui->tab2_nologin->setVisible(true);
    ui->tab3_nologin->setVisible(true);
    ui->tab4_nologin->setVisible(true);
    ui->tab5_nologin->setVisible(true);
    ui->tab1_logined->setVisible(false);
    ui->tab2_logined->setVisible(false);
    ui->tab3_logined->setVisible(false);
    ui->tab4_logined->setVisible(false);
    ui->tab5_logined->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get(QString str)
{
    return str;
}

void MainWindow::on_login_frame_login_clicked()
{
    QString loginid = ui->login_frame_id->text();
    QString password = ui->login_frame_word->text();
    int len = loginid.length();
    bool goodDigits = true;
    for(int i = 0; i < len;i++) if(loginid[i] < '0' || loginid[i] > '9') {
        ui->login_frame_id->setText("");
        ui->login_frame_word->setText("");
        //TODO : Alert Wrong Userid
        goodDigits = false;
    }
    if(goodDigits){
        QString tmp = get((QString)"login" + (QString)" " + loginid + (QString)" " + password);
        if(tmp[0] == '0')
        {
            ui->login_frame_id->setText("");
            ui->login_frame_word->setText("");
        }
        else
        {
            ui->loginFrame->setVisible(false);
            ui->userFrame->setVisible(true);
            ui->user_frame_auth->setText("您的权限级别为：");
            ui->user_frame_welcomeMessage->setText("欢迎您！");

            ui->tab1_nologin->setVisible(false);
            ui->tab2_nologin->setVisible(false);
            ui->tab3_nologin->setVisible(false);
            ui->tab4_nologin->setVisible(false);
            ui->tab5_nologin->setVisible(false);
            ui->tab1_logined->setVisible(true);
            ui->tab2_logined->setVisible(true);
            ui->tab3_logined->setVisible(true);
            ui->tab4_logined->setVisible(true);
            ui->tab5_logined->setVisible(true);
            if(loginid == "2018")
            {
                ui->user_frame_welcomeMessage->setText("欢迎您！冯思远，您暂时被禁止订票");
                on_login_frame_reset_clicked();
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

void MainWindow::on_user_frame_logout_clicked()
{
    ui->userFrame->setVisible(false);
    ui->loginFrame->setVisible(true);
    on_login_frame_reset_clicked();
}

void MainWindow::on_login_frame_reset_clicked()
{
    ui->login_frame_id->setText("");
    ui->login_frame_word->setText("");
    ui->tab1_nologin->setVisible(true);
    ui->tab2_nologin->setVisible(true);
    ui->tab3_nologin->setVisible(true);
    ui->tab4_nologin->setVisible(true);
    ui->tab5_nologin->setVisible(true);
    ui->tab1_logined->setVisible(false);
    ui->tab2_logined->setVisible(false);
    ui->tab3_logined->setVisible(false);
    ui->tab4_logined->setVisible(false);
    ui->tab5_logined->setVisible(false);
}

void MainWindow::on_tab5_nologin_frame_register_clicked()
{
    QString registerName = ui->tab5_nologin_frame_name->text();
    QString registerPassword = ui->tab5_nologin_frame_password->text();
    QString registerEmail = ui->tab5_nologin_frame_email->text();
    QString registerPhone = ui->tab5_nologin_frame_phone->text();
    if(registerPhone.length() != 11)ui->tab5_nologin_frame_phone->setText("");
    else
    {
        int len = registerEmail.length();
        bool flag = 0;
        for(int i = 0; i < len; i++)
        {
            if(registerEmail[i] == '@')
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            QString tmp = get((QString)"register" + (QString)" " + registerName + (QString)" " + registerPassword +
                              (QString)" " + registerEmail + (QString)" " + registerPhone);
            if(tmp[0] == '-')
            {
                ui->tab5_nologin_frame_name->setText("");
                ui->tab5_nologin_frame_password->setText("");
                ui->tab5_nologin_frame_email->setText("");
                ui->tab5_nologin_frame_phone->setText("");
            }
            else
            {
                ui->loginFrame->setVisible(false);
                ui->userFrame->setVisible(true);
                ui->user_frame_auth->setText("您的权限级别为：");
                ui->user_frame_welcomeMessage->setText("欢迎您！");
                ui->tab1_nologin->setVisible(false);
                ui->tab2_nologin->setVisible(false);
                ui->tab3_nologin->setVisible(false);
                ui->tab4_nologin->setVisible(false);
                ui->tab5_nologin->setVisible(false);
                ui->tab1_logined->setVisible(true);
                ui->tab2_logined->setVisible(true);
                ui->tab3_logined->setVisible(true);
                ui->tab4_logined->setVisible(true);
                ui->tab5_logined->setVisible(true);
                if(registerName == "hzfengsy")
                {
                    ui->user_frame_welcomeMessage->setText("欢迎您！冯思远，您暂时被禁止订票");
                    on_login_frame_reset_clicked();
                }
            }
        }
        else
        {
            ui->tab5_nologin_frame_email->setText("");
        }
    }
}

void MainWindow::on_tab4_logined_frame_usercheckid_clicked()
{
    QString tmp = get((QString)"query_profile" + (QString)" " + ui->tab4_logined_frame_userid->text());
    int len = tmp.length();
    if(len == 1)ui->tab4_logined_frame_username->setText("不存在该用户！");
    else
    {
        QString str = "";
        for(int i = 0; i < len; i++)
            if(tmp[i] == ' ')break;
            else str += tmp[i];
        ui->tab4_logined_frame_username->setText(str);
    }
}
