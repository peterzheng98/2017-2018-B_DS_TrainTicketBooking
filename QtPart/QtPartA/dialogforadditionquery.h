#ifndef DIALOGFORADDITIONQUERY_H
#define DIALOGFORADDITIONQUERY_H

#include <QDialog>

namespace Ui {
class DialogForAdditionQuery;
}

class DialogForAdditionQuery : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForAdditionQuery(QWidget *parent = 0);
    ~DialogForAdditionQuery();

private:
    Ui::DialogForAdditionQuery *ui;
};

#endif // DIALOGFORADDITIONQUERY_H
