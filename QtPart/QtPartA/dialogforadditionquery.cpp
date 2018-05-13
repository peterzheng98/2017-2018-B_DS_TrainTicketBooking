#include "dialogforadditionquery.h"
#include "ui_dialogforadditionquery.h"

DialogForAdditionQuery::DialogForAdditionQuery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogForAdditionQuery)
{
    ui->setupUi(this);
}

DialogForAdditionQuery::~DialogForAdditionQuery()
{
    delete ui;
}
