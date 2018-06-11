#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
