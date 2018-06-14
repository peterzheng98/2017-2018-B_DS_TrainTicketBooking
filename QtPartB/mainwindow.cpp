#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QString>
#include <QComboBox>

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
    if(!socket->waitForConnected(30000))
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
                ui->label_8->setVisible(false);
                ui->tab4_logined_frame_userid->setVisible(false);
                ui->tab4_logined_frame_usercheckid->setVisible(false);
                ui->tab4_logined_frame_modifyprivilege->setVisible(false);
                ui->tab4_logined_frame_modifyuserid->setVisible(false);
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

}

void MainWindow::tab2_reset()
{

}

void MainWindow::tab3_reset()
{

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
                ui->label_8->setVisible(false);
                ui->tab4_logined_frame_userid->setVisible(false);
                ui->tab4_logined_frame_usercheckid->setVisible(false);
                ui->tab4_logined_frame_modifyprivilege->setVisible(false);
                ui->tab4_logined_frame_modifyuserid->setVisible(false);
                ui->loginFrame->setVisible(false);
                ui->userFrame->setVisible(true);
                ui->user_frame_auth->setText("您的权限级别为：普通用户");
                ui->user_frame_welcomeMessage->setText((QString)"欢迎您！" + registerName +
                                                       (QString)"您的ID为：" + tmp + (QString)"（请牢记！）");
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
                      ui->tab4_logined_frame_userword->text() + (QString)" " +
                      ui->tab4_logined_frame_usermail->text() + (QString)" " +
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

    if(ui->tab4_logined_frame_transfer->isChecked())
    {
        tmp = get((QString)"query_transfer " + ui->tab1_logined_frame_loc1->text() + (QString)" " +
                   ui->tab1_logined_frame_loc2->text() + (QString)" " + ttmp + (QString)" " + catalog);
    }
    else
    {
        tmp = get((QString)"query_ticket " + ui->tab1_logined_frame_loc1->text() + (QString)" " +
                   ui->tab1_logined_frame_loc2->text() + (QString)" " + ttmp + (QString)" " + catalog);
    }
    ui->tab2_ticketShowing->clear();
    ui->tab2_ticketShowing->setRowCount(0);
    ui->tab2_ticketShowing->setColumnCount(6);//只设置列数，行数动态中增加
    ui->tab2_ticketShowing->setHorizontalHeaderLabels(QStringList()<<"始发站"<<"始发日期"<<"始发时间"
                                                      << "终点站" << "到达日期" << "到达时间");
    ui->tab2_ticketShowing->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tab2_ticketShowing->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tab2_ticketShowing->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    int len = tmp.length();
    int i = 0;
    QString str = "";
    for(; i < len; i++)
    {
        if(tmp[i] == '\n')break;
        str += tmp[i];
    }

    id.clear();
    seatKind.clear();
    seatRest.clear();
    seatCost.clear();

    int cnt = str.toInt();
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
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
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

QStringList idHistory;
QList<QStringList> seatKindHistory, seatRestHistory, seatCostHistory;

void MainWindow::on_tab3_logined_frame_search_clicked()
{
    QString catalog = "CDGKOTZ";
    QString ttmp = ui->tab3_logined_frame_date->text();
    int lentmp = ttmp.length();
    for(int i = 0; i < lentmp; i++)
        if(ttmp[i] == '/')ttmp[i] = '-';
    QString tmp = get((QString)"query_order " + userInfo.id + (QString)" " +
                  ttmp + (QString)" " + catalog);
    ui->tab3_ticketHistory->clear();
    ui->tab3_ticketHistory->setRowCount(0);
    qDebug() << ui->tab3_ticketHistory->rowCount() << "!!!????";
    ui->tab3_ticketHistory->setColumnCount(9);//只设置列数，行数动态中增加
    ui->tab3_ticketHistory->setHorizontalHeaderLabels(QStringList()<<"始发站"<<"始发日期"<<"始发时间"
                                                      << "终点站" << "到达日期" << "到达时间" << "座位类型"
                                                      << "购票数量" << "票价");
    ui->tab3_ticketHistory->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tab3_ticketHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->tab3_ticketHistory->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    int len = tmp.length();
    int i = 0;
    QString str = "";
    for(; i < len; i++)
    {
        if(tmp[i] == '\n')break;
        str += tmp[i];
    }

    idHistory.clear();
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
            nowSeatKind.push_back(str);
            str = "";
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
            }
            ui->tab3_ticketHistory->setItem(RowCont, 7, new QTableWidgetItem(str));
            nowSeatRest.push_back(str);
            str = "";
            for(i++; i < len; i++)
            {
                if(tmp[i] == '\n' || tmp[i] == ' ')break;
                else str += tmp[i];
            }
            ui->tab3_ticketHistory->setItem(RowCont, 8, new QTableWidgetItem(str));
            nowSeatCost.push_back(str);
            qDebug() << str;
        }
        seatKindHistory.push_back(nowSeatKind);
        seatRestHistory.push_back(nowSeatRest);
        seatCostHistory.push_back(nowSeatCost);
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    int nowx = ui->tab2_ticketShowing->currentRow(), nowy = ui->tab2_cata->currentIndex();
    if(nowy == -1)
    {
        QMessageBox::critical(NULL, "订票错误", "请单击要订的票！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    qDebug() << nowx << " !! ?? " << nowy;
    if(!(ui->tab2_ticketCount->text()).length())
    {
        QMessageBox::critical(NULL, "订票错误", "订票数量不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
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

void MainWindow::on_tab3_ticketHistory_clicked(const QModelIndex &index)
{
    //TODO 把选择的那一项的车次号显示在上面的文本框里面
}

void MainWindow::on_group_refund_button_clicked()
{
    if(!(ui->group_num->text()).length())
    {
        QMessageBox::critical(NULL, "订票错误", "订票数量不能为空！", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QString tmp = get((QString)"refund_ticket " + userInfo.id + (QString)" " + ui->group_num->text() +
                      /* Train ID  +*/ (QString)" " + /* loc1  +*/ (QString)" " + /* loc2  + */(QString)" " //+
                      /* Ticket Kind */);
    if(tmp == "") return;
    //TODO 发送订票
}
