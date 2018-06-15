#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QComboBox>

#include<iostream>
#include<string>

const int nowUserNum = 2017;

#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476
unsigned int strlength;
unsigned int atemp;
unsigned int btemp;
unsigned int ctemp;
unsigned int dtemp;
const unsigned int k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
        0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
        0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51,
        0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905,
        0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
        0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
        0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
        0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
        0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314,
        0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
//鍚戝乏浣嶇Щ鏁?
const unsigned int s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
                          12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                          4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
                          15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
const char str16[] = "0123456789abcdef";

void mainLoop(unsigned int M[]) {
    unsigned int f, g;
    unsigned int a = atemp;
    unsigned int b = btemp;
    unsigned int c = ctemp;
    unsigned int d = dtemp;
    for (unsigned int i = 0; i < 64; i++) {
        if (i < 16) {
            f = F(b, c, d);
            g = i;
        } else if (i < 32) {
            f = G(b, c, d);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(b, c, d);
            g = (3 * i + 5) % 16;
        } else {
            f = I(b, c, d);
            g = (7 * i) % 16;
        }
        unsigned int tmp = d;
        d = c;
        c = b;
        b = b + shift((a + f + k[i] + M[g]), s[i]);
        a = tmp;
    }
    atemp = a + atemp;
    btemp = b + btemp;
    ctemp = c + ctemp;
    dtemp = d + dtemp;
}

unsigned int *add(std::string str) {
    unsigned int num = ((str.length() + 8) / 64) + 1;
    unsigned int *strByte = new unsigned int[num * 16];
    strlength = num * 16;
    for (unsigned int i = 0; i < num * 16; i++)
        strByte[i] = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
        strByte[i >> 2] |= (str[i]) << ((i % 4) * 8);
    }
    strByte[str.length() >> 2] |= 0x80 << (((str.length() % 4)) * 8);
    strByte[num * 16 - 2] = str.length() * 8;
    return strByte;
}

std::string changeHex(int a) {
    int b;
    std::string str1;
    std::string str = "";
    for (int i = 0; i < 4; i++) {
        str1 = "";
        b = ((a >> i * 8) % (1 << 8)) & 0xff;
        for (int j = 0; j < 2; j++) {
            str1.insert(0, 1, str16[b % 16]);
            b = b / 16;
        }
        str += str1;
    }
    return str;
}

std::string getMD5(std::string source) {
    atemp = A;
    btemp = B;
    ctemp = C;
    dtemp = D;
    unsigned int *strByte = add(source);
    for (unsigned int i = 0; i < strlength / 16; i++) {
        unsigned int num[16];
        for (unsigned int j = 0; j < 16; j++)
            num[j] = strByte[i * 16 + j];
        mainLoop(num);
    }
    return changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp));
}

struct UserInfo{
    QString id;
    int privilege;
}userInfo;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);

    ui->radioButton->setChecked(true);
    ui->userFrame->setVisible(false);

    ui->tab2_ticketShowing->setColumnCount(6);//只设置列数，行数动态中增加
    ui->tab2_ticketShowing->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tab2_ticketShowing->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tab2_ticketShowing->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    ui->tab2_ticketShowing->setHorizontalHeaderLabels(QStringList()<<"始发站"<<"始发日期"<<"始发时间"
                                                      << "终点站" << "到达日期" << "到达时间");
    ui->tab2_ticketShowing->show();

    ui->tab3_ticketHistory->setColumnCount(9);//只设置列数，行数动态中增加
    ui->tab3_ticketHistory->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tab3_ticketHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tab3_ticketHistory->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    ui->tab3_ticketHistory->setHorizontalHeaderLabels(QStringList()<<"始发站"<<"始发日期"<<"始发时间"
                                                      << "终点站" << "到达日期" << "到达时间" << "座位类型"
                                                      << "购票数量" << "票价");
    ui->tab3_ticketHistory->show();

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
    if(socket)delete socket;
    delete ui;
}

void MainWindow::socket_Read_Data()
{
    qDebug() << "yeah!";
    QByteArray buffer;
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->tmpText->toPlainText();
        str += buffer;
        ui->tmpText->setText(str);
    }
    qDebug() << buffer.length();
}

void MainWindow::socket_Disconnected()
{
    socket->close();
}

void MainWindow::work(QString str)
{
    qDebug() << "Send: " << str;
    QTextCodec *code= QTextCodec::codecForName("UTF-8");
    QByteArray bytest = code->fromUnicode(str);
    socket->write(bytest);
    socket->flush();
}

QString MainWindow::get(QString str)
{
    socket->abort();
    socket->connectToHost("101.132.131.164", 10774);
    if(!socket->waitForConnected(3000))
    {
        QMessageBox::critical(NULL, "网络错误", "连接失败！", QMessageBox::Yes, QMessageBox::Yes);
        qDebug() << "Connection failed!";
        return "";
    }
    qDebug() << "Connect successfully!";
    work(str);
    ui->tmpText->setText("");
    while(socket->waitForReadyRead());
    socket->close();
    return ui->tmpText->toPlainText();
}

void MainWindow::do_with_privilege()
{
    ui->label_8->setVisible(false);
    ui->tab4_logined_frame_userid->setVisible(false);
    ui->tab4_logined_frame_usercheckid->setVisible(false);
    ui->tab4_logined_frame_modifyprivilege->setVisible(false);
    ui->tab4_logined_frame_modifyuserid->setVisible(false);
    ui->tab3_logined_frame_userid->setVisible(false);
    ui->label_22->setVisible(false);
}

void MainWindow::on_login_frame_login_clicked()
{
    QString loginid = ui->login_frame_id->text();
    QString password = ui->login_frame_word->text();
    int lenid = loginid.length();
    int lenpass = password.length();
    if(!lenid || ! lenpass)
    {
        QMessageBox::critical(NULL, "登陆错误", "用户名或密码不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    int nowid = loginid.toInt();
    if(nowid < 2018)
    {
        QMessageBox::critical(NULL, "登录错误", "用户ID不在范围内！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else
    {
        if(loginid.toInt() > nowUserNum)password = QString::fromStdString(getMD5(password.toStdString()));
        QString tmp = get((QString)"login" + (QString)" " + loginid + (QString)" " + password);
        if(tmp == "")return;
        if(tmp[0] != '1')
        {
            QMessageBox::critical(NULL, "登录错误", "用户ID或密码错误！", QMessageBox::Yes, QMessageBox::Yes);
            ui->login_frame_id->setText("");
            ui->login_frame_word->setText("");
        }
        else
        {
            ui->userInfo_id->setText((QString)"您的ID： " + loginid);
            tmp = get((QString)"query_profile" + (QString)" " + loginid);
            if(tmp == "")return;
            int len = tmp.length();
            userInfo.id = loginid;
            int flag = 2;
            for(int i = len - 1; i >= 0; i--)
                if(tmp[i] >= '0' && tmp[i] <= '9')
                {
                    if(tmp[i] == '1')flag = 1;
                    else flag = 2;
                    break;
                }
            QString nowName = "";
            for(int i = 0; i < len; i++)
                if(tmp[i] == ' ')break;
                else nowName += tmp[i];
            if(flag == 1)
            {
                userInfo.privilege = 1;
                do_with_privilege();
            }
            else userInfo.privilege = 2;
            ui->loginFrame->setVisible(false);
            ui->userFrame->setVisible(true);
            ui->user_frame_auth->setText((QString)"您的权限级别为：" + (QString)(userInfo.privilege == 1 ? "普通用户" : "管理员"));
            ui->user_frame_welcomeMessage->setText((QString)"欢迎您！" + nowName);
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

void MainWindow::tab1_reset()
{
    ui->radioButton->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->tab1_logined_frame_date->setDate(ui->tab1_logined_frame_date->date());
    ui->tab1_logined_frame_loc1->setText("");
    ui->tab1_logined_frame_loc2->setText("");
    on_addTrainBox_reset_clicked();
    ui->tab4_logined_frame_transfer->setChecked(false);
}

void MainWindow::tab2_reset()
{
    ui->tab2_ticketShowing->clearContents();
    ui->tab2_ticketShowing->setRowCount(0);
    ui->tab2_ticketCount->setText("");
    ui->tab2_remain->setText("余票");
    ui->tab2_price->setText("票价");
    ui->tab2_chosen->setText("");
    ui->tab2_cata->clear();
}

void MainWindow::tab3_reset()
{
    ui->group_num->setText("");
    ui->group_tid->setText("");
    ui->tab3_logined_frame_date->setDate(ui->tab3_logined_frame_date->date());
    ui->tab3_ticketHistory->clearContents();
    ui->tab3_ticketHistory->setRowCount(0);
    ui->tab3_logined_frame_userid->setText("");
}

void MainWindow::tab4_reset()
{
    ui->tab4_logined_frame_username->setText("");
    ui->tab4_logined_frame_userword->setText("");
    ui->tab4_logined_frame_userword_2->setText("");
    ui->tab4_logined_frame_userid->setText("");
    ui->tab4_logined_frame_modifyuserid->setText("");
    ui->tab4_logined_frame_userphone->setText("");
    ui->tab4_logined_frame_usermail->setText("");
    ui->label_8->setVisible(true);
    ui->tab4_logined_frame_userid->setVisible(true);
    ui->tab4_logined_frame_usercheckid->setVisible(true);
    ui->tab4_logined_frame_modifyprivilege->setVisible(true);
    ui->tab4_logined_frame_modifyuserid->setVisible(true);
}

void MainWindow::tab5_reset()
{
    ui->tab5_nologin_frame_email->setText("");
    ui->tab5_nologin_frame_name->setText("");
    ui->tab5_nologin_frame_password->setText("");
    ui->tab5_nologin_frame_phone->setText("");
    ui->userInfo_id->setText("");
}

void MainWindow::on_user_frame_logout_clicked()
{
    ui->userFrame->setVisible(false);
    ui->loginFrame->setVisible(true);
    on_login_frame_reset_clicked();
    tab1_reset();
    tab2_reset();
    tab3_reset();
    tab4_reset();
    tab5_reset();
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
    if(registerName.length() == 0)
    {
        QMessageBox::critical(NULL, "注册错误", "用户名不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString registerPassword = ui->tab5_nologin_frame_password->text();
    if(registerPassword.length() == 0)
    {
        QMessageBox::critical(NULL, "注册错误", "密码不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString registerEmail = ui->tab5_nologin_frame_email->text();
    if(registerEmail.length() == 0)
    {
        QMessageBox::critical(NULL, "注册错误", "邮箱不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString registerPhone = ui->tab5_nologin_frame_phone->text();
    if(registerPhone.length() == 0)
    {
        QMessageBox::critical(NULL, "注册错误", "手机号码不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(registerPhone.length() != 11)
    {
        ui->tab5_nologin_frame_phone->setText("");
        QMessageBox::critical(NULL, "注册错误", "手机号码不合法！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
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
            registerPassword = QString::fromStdString(getMD5(registerPassword.toStdString()));
            QString tmp = get((QString)"register" + (QString)" " + registerName + (QString)" " + registerPassword +
                              (QString)" " + registerEmail + (QString)" " + registerPhone);
            if(tmp.length() == 0)return;
            if(tmp[0] == '-')
            {
                ui->tab5_nologin_frame_name->setText("");
                ui->tab5_nologin_frame_password->setText("");
                ui->tab5_nologin_frame_email->setText("");
                ui->tab5_nologin_frame_phone->setText("");
                QMessageBox::critical(NULL, "注册错误", "注册失败！", QMessageBox::Yes, QMessageBox::Yes);
                return;
            }
            else
            {
                userInfo.id = tmp;
                userInfo.privilege = 1;
                do_with_privilege();
                ui->loginFrame->setVisible(false);
                ui->userFrame->setVisible(true);
                ui->user_frame_auth->setText("您的权限级别为：普通用户");
                ui->user_frame_welcomeMessage->setText((QString)"欢迎您！" + registerName);
                ui->userInfo_id->setText((QString)"您的ID： " + userInfo.id);
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
            QMessageBox::critical(NULL, "注册错误", "邮箱不合法！", QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
}

void MainWindow::on_tab4_logined_frame_usercheckid_clicked()
{
    QString tmp = get((QString)"query_profile" + (QString)" " + ui->tab4_logined_frame_userid->text());
    int len = tmp.length();
    qDebug() << tmp[0];
    if(tmp[0] == '0')
    {
        QMessageBox::critical(NULL, "查询用户信息错误", "查询用户信息失败！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else
    {
        QString str = "";
        int i = 0;
        for(; i < len; i++)
            if(tmp[i] == ' ')break;
            else str += tmp[i];
        ui->tab4_logined_frame_username->setText(str);
        str = "";
        for(i++; i < len; i++)
            if(tmp[i] == ' ')break;
            else str += tmp[i];
        ui->tab4_logined_frame_usermail->setText(str);
        str = "";
        for(i++; i < len; i++)
            if(tmp[i] == ' ')break;
            else str += tmp[i];
        ui->tab4_logined_frame_userphone->setText(str);
    }
}

void MainWindow::on_tab4_logined_frame_modifyinfo_clicked()
{
    QString registerName = ui->tab4_logined_frame_username->text();
    if(registerName.length() == 0)
    {
        QMessageBox::critical(NULL, "修改信息错误", "用户名不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString registerPassword = ui->tab4_logined_frame_userword->text();
    if(registerPassword.length() == 0)
    {
        QMessageBox::critical(NULL, "修改信息错误", "密码不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString registerEmail = ui->tab4_logined_frame_usermail->text();
    if(registerEmail.length() == 0)
    {
        QMessageBox::critical(NULL, "修改信息错误", "邮箱不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString registerPhone = ui->tab4_logined_frame_userphone->text();
    if(registerPhone.length() == 0)
    {
        QMessageBox::critical(NULL, "修改信息错误", "手机号码不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(registerPhone.length() != 11)
    {
        ui->tab4_logined_frame_userphone->setText("");
        QMessageBox::critical(NULL, "修改信息错误", "手机号码不合法！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(ui->tab4_logined_frame_userword->text() != ui->tab4_logined_frame_userword_2->text())
    {
        QMessageBox::critical(NULL, "修改信息错误", "两次密码不同！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString tmp = get((QString)"modify_profile" + (QString)" " + userInfo.id + (QString)" " +
                      ui->tab4_logined_frame_username->text() + (QString)" " +
                      QString::fromStdString(getMD5(ui->tab4_logined_frame_userword->text().toStdString())) +
                      (QString)" " + ui->tab4_logined_frame_usermail->text() + (QString)" " +
                      ui->tab4_logined_frame_userphone->text());
    if(tmp == "")return;
    if(tmp[0] != '1')
    {
        QMessageBox::critical(NULL, "修改信息错误", "修改信息失败！", QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(NULL, "修改信息成功", "修改信息成功！", QMessageBox::Yes, QMessageBox::Yes);
    }
    tab4_reset();
}

void MainWindow::on_tab4_logined_frame_modifyprivilege_clicked()
{
    QString modifyUserID = ui->tab4_logined_frame_modifyuserid->text();
    if(modifyUserID.length() == 0)
    {
        QMessageBox::critical(NULL, "提升权限错误", "用户ID不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString tmp = get((QString)"modify_privilege" + (QString)" " + userInfo.id + (QString)" " +
                      modifyUserID + (QString)" " + (QString)"2");
    if(tmp == "")return;
    if(tmp[0] != '1')
    {
        QMessageBox::critical(NULL, "提升权限错误", "提升权限失败！", QMessageBox::Yes, QMessageBox::Yes);
        ui->tab4_logined_frame_modifyuserid->setText("");
    }
    else
    {
        QMessageBox::information(NULL, "提升权限成功", "提升权限成功！", QMessageBox::Yes, QMessageBox::Yes);
    }
}

QStringList id;
QList<QStringList> seatKind, seatRest, seatCost;

void MainWindow::on_tab4_logined_frame_search_clicked()
{
    QString tmp = "", catalog = "";
    int f1 = ui->radioButton->isChecked();
    int f2 = ui->radioButton_2->isChecked();
    int f3 = ui->radioButton_3->isChecked();
    if(f1)catalog = "CDGKOTZ";
    if(f2)catalog = "GD";
    if(f3)catalog = "CKOTZ";
    qDebug() << catalog;
    QString ttmp = ui->tab1_logined_frame_date->text();
    int lentmp = ttmp.length();
    for(int i = 0; i < lentmp; i++)
        if(ttmp[i] == '/')ttmp[i] = '-';
    int transferflag = 0;
    if(ui->tab1_logined_frame_loc1->text() == "" || ui->tab1_logined_frame_loc2->text() == "")
    {
        QMessageBox::critical(NULL, "查询车票错误", "出发地和目的地不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    if(ui->tab4_logined_frame_transfer->isChecked())
    {
        if(userInfo.privilege == 2)
        {
            tmp = get((QString)"query_transfer " + ui->tab1_logined_frame_loc1->text() + (QString)" " +
                   ui->tab1_logined_frame_loc2->text() + (QString)" " + ttmp + (QString)" " + catalog);
            transferflag = 1;
        }
        else
        {
            QMessageBox::critical(NULL, "查询车票错误", "您需要支付$5来获取这个功能！", QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    else
    {
        transferflag = 0;
        tmp = get((QString)"query_ticket " + ui->tab1_logined_frame_loc1->text() + (QString)" " +
                   ui->tab1_logined_frame_loc2->text() + (QString)" " + ttmp + (QString)" " + catalog);
    }
    ui->tab2_ticketShowing->clearContents();
    ui->tab2_ticketShowing->setRowCount(0);

    int len = tmp.length();
    int i = 0;
    QString str = "";
    int cnt = 0;
    if(transferflag)cnt = 2;
    else
    {
        for(; i < len; i++)
        {
            if(tmp[i] == '\n')break;
            str += tmp[i];
        }
        cnt = str.toInt();
    }

    id.clear();
    seatKind.clear();
    seatRest.clear();
    seatCost.clear();

    for(int k = 0; k < cnt; k++)
    {
        int RowCont = ui->tab2_ticketShowing->rowCount();
        ui->tab2_ticketShowing->insertRow(RowCont);
        while(!((tmp[i] <= '9' && tmp[i] >= '0') || (tmp[i] <= 'z' && tmp[i] >= 'a') || (tmp[i] <= 'Z' && tmp[i] >= 'A')))i++;
        str = "";
        for(; i < len; i++)
        {
            if(tmp[i] == ' ')break;
            str += tmp[i];
        }
        qDebug() << str;
        id.push_back(str);
        for(int l = 0; l < 6; l++)
        {
            str = "";
            for(i++; i < len; i++)
            {
                if(tmp[i] == ' ')break;
                str += tmp[i];
            }
            ui->tab2_ticketShowing->setItem(RowCont, l, new QTableWidgetItem(str));
        }
        QStringList nowSeatKind, nowSeatRest, nowSeatCost;
        nowSeatKind.clear();
        nowSeatRest.clear();
        nowSeatCost.clear();
        int cnt = 0;
        for(int j = i + 1; j < len && tmp[j] != '\n'; j++)
            if(tmp[j] == ' ' && tmp[j - 1] != ' ')cnt++;
        qDebug() << cnt;
        for(int j = 0; j < cnt / 3; j++)
        {
            str = "";
            for(i++ ; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
            }
            nowSeatKind.push_back(str);
            str = "";
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
            }
            nowSeatRest.push_back(str);
            str = "";
            int cnt = 0, flag = 0;
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else
                {
                    if(!flag || cnt < 2)str += tmp[i];
                    if(flag)cnt++;
                    if(cnt == 2 && tmp[i] >= '5')str = QString::number(str.toDouble() + 0.01, 'f', 2);
                    if(tmp[i] == '.')flag = 1;
                }
            }
            nowSeatCost.push_back(str);
            qDebug() << str;
        }
        seatKind.push_back(nowSeatKind);
        seatRest.push_back(nowSeatRest);
        seatCost.push_back(nowSeatCost);
    }
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_tab2_ticketShowing_clicked(const QModelIndex &index)
{
    int now = ui->tab2_ticketShowing->currentRow();
    ui->tab2_chosen->setText(id[now]);
    qDebug() << id[now];
    ui->tab2_cata->clear();
    ui->tab2_cata->addItems(seatKind[now]);
}

void MainWindow::on_tab2_cata_currentIndexChanged(int index)
{
    if(index >= 0)
    {
        qDebug() << index << " " << ui->tab2_ticketShowing->currentRow() << " " << seatCost[ui->tab2_ticketShowing->currentRow()].size();
        ui->tab2_price->setText((QString)"票价 " + seatCost[ui->tab2_ticketShowing->currentRow()][index]);
        ui->tab2_remain->setText((QString)"余票 " + seatRest[ui->tab2_ticketShowing->currentRow()][index]);
    }
}

QStringList idHistory, seatKindHistory, seatRestHistory, seatCostHistory, loc1History, loc2History, dateHistory;
QList<int> belong;

void MainWindow::on_tab3_logined_frame_search_clicked()
{
    QString catalog = "CDGKOTZ";
    QString ttmp = ui->tab3_logined_frame_date->text();
    int lentmp = ttmp.length();
    for(int i = 0; i < lentmp; i++)
        if(ttmp[i] == '/')ttmp[i] = '-';
    QString searchUser = ui->tab3_logined_frame_userid->text();
    if(searchUser == "")searchUser = userInfo.id;
    QString tmp = get((QString)"query_order " + searchUser + (QString)" " +
                  ttmp + (QString)" " + catalog);
    ui->tab3_ticketHistory->clearContents();
    ui->tab3_ticketHistory->setRowCount(0);

    int len = tmp.length();
    int i = 0;
    QString str = "";
    for(; i < len; i++)
    {
        if(tmp[i] == '\n')break;
        str += tmp[i];
    }

    belong.clear();
    idHistory.clear();
    dateHistory.clear();
    loc1History.clear();
    loc2History.clear();
    seatKindHistory.clear();
    seatRestHistory.clear();
    seatCostHistory.clear();

    int cnt = str.toInt();
    for(int k = 0; k < cnt; k++)
    {
        int RowCont = ui->tab3_ticketHistory->rowCount();
        ui->tab3_ticketHistory->insertRow(RowCont);
        str = "";
        while(!((tmp[i] <= '9' && tmp[i] >= '0') || (tmp[i] <= 'z' && tmp[i] >= 'a') || (tmp[i] <= 'Z' && tmp[i] >= 'A')))i++;
        for(; i < len; i++)
        {
            if(tmp[i] == ' ')break;
            str += tmp[i];
        }
        qDebug() << str;
        idHistory.push_back(str);
        for(int l = 0; l < 6; l++)
        {
            str = "";
            for(i++; i < len; i++)
            {
                if(tmp[i] == ' ')break;
                str += tmp[i];
            }
            ui->tab3_ticketHistory->setItem(RowCont, l, new QTableWidgetItem(str));
            if(l == 0)loc1History.push_back(str);
            if(l == 1)dateHistory.push_back(str);
            if(l == 3)loc2History.push_back(str);
        }
        QStringList nowSeatKind, nowSeatRest, nowSeatCost;
        nowSeatKind.clear();
        nowSeatRest.clear();
        nowSeatCost.clear();
        int tot = 0;
        for(int j = i + 1; j < len && tmp[j] != '\n'; j++)
            if(tmp[j] == ' ' && tmp[j - 1] != ' ')tot++;
        qDebug() << tot;
        for(int j = 0; j < tot / 3; j++)
        {
            belong.push_back(k);
            if(j > 0)
            {
                RowCont = ui->tab3_ticketHistory->rowCount();
                ui->tab3_ticketHistory->insertRow(RowCont);
            }
            str = "";
            for(i++ ; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
            }
            ui->tab3_ticketHistory->setItem(RowCont, 6, new QTableWidgetItem(str));
            seatKindHistory.push_back(str);
            str = "";
            int toDelete = 0;
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
            }
            if(str.toInt() == 0)toDelete = 1;
            ui->tab3_ticketHistory->setItem(RowCont, 7, new QTableWidgetItem(str));
            seatRestHistory.push_back(str);
            str = "";
            int cnt = 0, flag = 0;
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else
                {
                    if(!flag || cnt < 2)str += tmp[i];
                    if(flag)cnt++;
                    if(cnt == 2 && tmp[i] >= '5')str = QString::number(str.toDouble() + 0.01, 'f', 2);
                    if(tmp[i] == '.')flag = 1;
                }
            }
            ui->tab3_ticketHistory->setItem(RowCont, 8, new QTableWidgetItem(str));
            seatCostHistory.push_back(str);
            if(toDelete == 1)
            {
                ui->tab3_ticketHistory->removeRow(RowCont);
                belong.pop_back();
                seatKindHistory.pop_back();
                seatRestHistory.pop_back();
                seatCostHistory.pop_back();
            }
            qDebug() << str;
        }
    }
}

void MainWindow::on_tab3_ticketHistory_clicked(const QModelIndex &index)
{
    int now = ui->tab3_ticketHistory->currentRow();
    qDebug() << now;
    if(now >= 0)
    {
        ui->group_tid->setText(idHistory[belong[now]]);
        qDebug() << seatKindHistory[now] << " " << seatRestHistory[now] << " " << seatCostHistory[now];
        qDebug() << loc1History[belong[now]] << " " << loc2History[belong[now]];
    }
}

void MainWindow::on_group_refund_button_clicked()
{
    int now = ui->tab3_ticketHistory->currentRow();
    if(ui->group_num->text() == "" || now == -1)
    {
        QMessageBox::critical(NULL, "退票错误", "请单击要退票的订单！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    int nowNum = ui->group_num->text().toInt();
    if(!(ui->group_num->text()).length())
    {
        QMessageBox::critical(NULL, "退票错误", "退票数量不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(nowNum > seatRestHistory[now].toInt())
    {
        QMessageBox::critical(NULL, "退票错误", "退票数量不能大于订票数量！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(!nowNum)
    {
        QMessageBox::critical(NULL, "退票错误", "退票数量不能为0！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString tmp = get((QString)"refund_ticket " + userInfo.id + (QString)" " + ui->group_num->text() + (QString)" " +
                      idHistory[belong[now]] + (QString)" " + loc1History[belong[now]]  + (QString)" " + loc2History[belong[now]] +
                      (QString)" " + dateHistory[belong[now]] + (QString)" " + seatKindHistory[now]);
    if(tmp == "") return;
    if(tmp[0] == '1')
    {
        ui->tab3_logined_frame_search->click();
        ui->group_num->setText("");
        ui->group_tid->setText("");
        QMessageBox::information(NULL, "退票成功", "退票成功！", QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        QMessageBox::critical(NULL, "退票错误", "退票失败！", QMessageBox::Yes, QMessageBox::Yes);
    }
}

void MainWindow::on_tab2_booking_clicked()
{
    int nowx = ui->tab2_ticketShowing->currentRow(), nowy = ui->tab2_cata->currentIndex();
    if(nowy == -1)
    {
        QMessageBox::critical(NULL, "订票错误", "请单击要订的车次！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    qDebug() << nowx << " !! ?? " << nowy;
    if(!(ui->tab2_ticketCount->text()).length())
    {
        QMessageBox::critical(NULL, "订票错误", "订票数量不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if((ui->tab2_ticketCount->text()).toInt() == 0)
    {
        QMessageBox::critical(NULL, "订票错误", "订票数量不能为零！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(ui->tab2_ticketCount->text().toInt() > seatRest[nowx][nowy].toInt())
    {
        QMessageBox::critical(NULL, "订票错误", "余票不足！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    double cost = seatCost[nowx][nowy].toDouble() * ui->tab2_ticketCount->text().toInt();
    QMessageBox message(QMessageBox::NoIcon, "请支付", (QString)"您需要支付￥" + QString::number(cost, 'f', 2) + (QString)"请扫描左边二维码！");
    message.setIconPixmap(QPixmap(":/new/label/QR.jpg"));
    message.exec();
    QString nowdate = ui->tab2_ticketShowing->item(nowx, 1)->text();
    QString tmp = get((QString)"buy_ticket " + userInfo.id + (QString)" " + ui->tab2_ticketCount->text() +
                      (QString)" " + id[nowx] + (QString)" " +
                      ui->tab1_logined_frame_loc1->text() + (QString)" " + ui->tab1_logined_frame_loc2->text() +
                      (QString)" " + nowdate + (QString)" " + ui->tab2_cata->currentText());
    if(tmp == "")return;
    int nowRest = seatRest[nowx][nowy].toInt() - (ui->tab2_ticketCount->text()).toInt();
    seatRest[nowx][nowy] = QString::number(nowRest);
    ui->tab2_remain->setText((QString)"余票 " + seatRest[nowx][nowy]);
}

void MainWindow::on_addTrainBox_reset_clicked()
{
    /*ui->addTrainBox_tid->setText("");
    ui->addTrainBox_tname->setText("");
    ui->addTrainBox_stat_num->setValue(1);
    ui->addTrainBox_price_num->setValue(1);*/
}

void MainWindow::on_pushButton_9_clicked()
{
    tab2_reset();
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    int nowx = ui->addTrainBox_stat_num->text().toInt();
    int nowy = ui->addTrainBox_price_num->text().toInt();
    ui->add_train->setRowCount(nowx);
    ui->add_train->setColumnCount(nowy + 4);
    ui->add_ticketname->setRowCount(1);
    QStringList headers;
    ui->add_ticketname->setColumnCount(nowy);
    for(int i = 1; i <= nowy; i++)
        headers.push_back((QString)"座位种类" + QString::number(i));
    ui->add_ticketname->setHorizontalHeaderLabels(headers);
    ui->add_ticketname->setVerticalHeaderLabels(QStringList() << "座位名称");
    headers.clear();
    headers << "车站名称" << "出站时间" << "到站时间" << "停站时长";
    for(int i = 1; i <= nowy; i++)
        headers.push_back((QString)"票价" + QString::number(i));
    ui->add_train->setHorizontalHeaderLabels(headers);
}

void MainWindow::on_choose_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), NULL, tr("*.*"));
    if(!fileName.isEmpty())
    {
        ui->file->setText(fileName);
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString sText = file.readAll();
            file.close();
            QString tmp = get(sText);
            if(tmp == "")return;
            if(tmp[0] != '1')
            {
                QMessageBox::critical(NULL, "登录错误", "用户ID或密码错误！", QMessageBox::Yes, QMessageBox::Yes);
                ui->login_frame_id->setText("");
                ui->login_frame_word->setText("");
            }
            else
            {
                QString loginid = "";
                int len = sText.length();
                int i = 0;
                for(; i < len; i++)
                    if(sText[i] == ' ')break;
                for(i++; i < len; i++)
                    if(sText[i] == ' ')break;
                    else loginid += sText[i];
                tmp = get((QString)"query_profile" + (QString)" " + loginid);
                if(tmp == "")return;
                len = tmp.length();
                userInfo.id = loginid;
                ui->userInfo_id->setText((QString)"您的ID： " + loginid);
                int flag = 2;
                for(int i = len - 1; i >= 0; i--)
                    if(tmp[i] >= '0' && tmp[i] <= '9')
                    {
                        if(tmp[i] == '1')flag = 1;
                        else flag = 2;
                        break;
                    }
                QString nowName = "";
                for(int i = 0; i < len; i++)
                    if(tmp[i] == ' ')break;
                    else nowName += tmp[i];
                if(flag == 1)
                {
                    userInfo.privilege = 1;
                    do_with_privilege();
                }
                else userInfo.privilege = 2;
                ui->loginFrame->setVisible(false);
                ui->userFrame->setVisible(true);
                ui->user_frame_auth->setText((QString)"您的权限级别为：" + (QString)(userInfo.privilege == 1 ? "普通用户" : "管理员"));
                ui->user_frame_welcomeMessage->setText((QString)"欢迎您！" + nowName);
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
}

void MainWindow::on_addTrainBox_button_add_2_clicked()
{
    QString str = "add_train " + ui->add_train_id->text() + " " + ui->add_train_name->text() + " " +
            ui->add_train_cata->text() + " " + ui->addTrainBox_stat_num->text() + " " +
            ui->addTrainBox_price_num->text();
    for(int i = 0; i < ui->add_ticketname->columnCount(); i++)
        if(ui->add_ticketname->item(0,i)!=NULL)
        {
            qDebug()<<ui->add_ticketname->item(0,i)->text();
            str += " " + ui->add_ticketname->item(0,i)->text();
        }
        else
        {
            QMessageBox::critical(NULL, "添加火车错误", "座位名称不能为空！", QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    qDebug() << str;
    for(int i = 0; i < ui->add_train->rowCount(); i++)
    {
        str += '\n';
        for(int j = 0; j < ui->add_train->columnCount(); j++)
            if(ui->add_train->item(i, j) != NULL)
            {
                if(j < 4)str += ui->add_train->item(i, j)->text() + " ";
                else
                {
                    str += ui->add_train->item(i, j)->text();
                    if(j < ui->add_train->columnCount() - 1)str += " ";
                }
            }
            else
            {
                QMessageBox::critical(NULL, "添加火车错误", "火车信息不能为空！", QMessageBox::Yes, QMessageBox::Yes);
                return;
            }
    }
    qDebug() << str;
    QString tmp = get(str);
    qDebug() << tmp;
    if(tmp == "")return;
    if(tmp[0] == '0')
    {
        QMessageBox::critical(NULL, "添加火车错误", "添加火车失败！", QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(NULL, "添加火车成功", "添加火车成功", QMessageBox::Yes, QMessageBox::Yes);
    }
}

void MainWindow::on_addTrainBox_reset_2_clicked()
{
    ui->add_train->clear();
    ui->add_train->setRowCount(0);
    ui->add_train->setColumnCount(0);
    ui->add_ticketname->clear();
    ui->add_ticketname->setRowCount(0);
    ui->add_ticketname->setColumnCount(0);
    ui->add_train_cata->setText("");
    ui->add_train_id->setText("");
    ui->add_train_name->setText("");
    ui->addTrainBox_stat_num->setValue(1);
    ui->addTrainBox_price_num->setValue(1);
}
