#include "loginui.h"
#include "ui_loginui.h"

LoginUI::LoginUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginUI)
{
    ui->setupUi(this);
}

LoginUI::~LoginUI()
{
    delete ui;
}
