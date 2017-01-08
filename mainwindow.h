#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calculate.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddChar(QString ch);
    int flag;

private slots:
    void on_pushButton7_clicked();

    void on_pushButtonRight_clicked();

    void on_pushButton8_clicked();

    void on_pushButton9_clicked();

    void on_pushButtonPlus_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_pushButton6_clicked();

    void on_pushButtonSub_clicked();

    void on_pushButton3_clicked();

    void on_pushButton2_clicked();

    void on_pushButton1_clicked();

    void on_pushButtonMul_clicked();

    void on_pushButton0_clicked();

    void on_pushButtonPoint_clicked();

    void on_pushButtonDiv_clicked();

    void on_pushButtonLeft_clicked();

    void on_pushButtonEqual_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    Calculate cal;
};

#endif // MAINWINDOW_H
