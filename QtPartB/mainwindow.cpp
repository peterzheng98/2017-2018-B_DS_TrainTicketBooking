#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->tab1_logined->setVisible(false);
    ui->tab2_logined->setVisible(false);
    ui->tab3_logined->setVisible(false);
    ui->tab4_logined->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    //TODO : checkUser
    //TODO : Accepted
    ui->loginFrame->setVisible(false);
    ui->userFrame->setVisible(true);
    ui->user_frame_auth->setText("您的权限级别为：");
    ui->user_frame_welcomeMessage->setText("欢迎您！");

    ui->tab1_nologin->setVisible(false);
    ui->tab2_nologin->setVisible(false);
    ui->tab3_nologin->setVisible(false);
    ui->tab4_nologin->setVisible(false);
    ui->tab1_logined->setVisible(true);
    ui->tab2_logined->setVisible(true);
    ui->tab3_logined->setVisible(true);
    ui->tab4_logined->setVisible(true);
    if(loginid == "2018") {
        ui->user_frame_welcomeMessage->setText("欢迎您！冯思远，您暂时被禁止订票");
        on_login_frame_reset_clicked();
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
    ui->tab1_logined->setVisible(false);
    ui->tab2_logined->setVisible(false);
    ui->tab3_logined->setVisible(false);
    ui->tab4_logined->setVisible(false);
}
