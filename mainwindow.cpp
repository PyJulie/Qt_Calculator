#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"
#include "QMessageBox"
#include "string"
#include <QFileDialog>
#include <fstream>
#include <qdebug.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonClear->setStyleSheet("color:red;");
    flag = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton7_clicked()
{
    QString str= "7";
    AddChar(str);
}


void MainWindow::on_pushButton8_clicked()
{
    QString str= "8";
    AddChar(str);
}

void MainWindow::on_pushButton9_clicked()
{
    QString str= "9";
    AddChar(str);
}

void MainWindow::on_pushButtonPlus_clicked()
{
    QString str= "+";
    AddChar(str);
}

void MainWindow::on_pushButton4_clicked()
{
    QString str= "4";
    AddChar(str);
}

void MainWindow::on_pushButton5_clicked()
{
    QString str= "5";
    AddChar(str);
}

void MainWindow::on_pushButton6_clicked()
{
    QString str= "6";
    AddChar(str);
}

void MainWindow::on_pushButtonSub_clicked()
{
    QString str= "-";
    AddChar(str);
}

void MainWindow::on_pushButton3_clicked()
{
    QString str= "3";
    AddChar(str);
}

void MainWindow::on_pushButton2_clicked()
{
    QString str= "2";
    AddChar(str);
}

void MainWindow::on_pushButton1_clicked()
{
    QString str= "1";
    AddChar(str);
}

void MainWindow::on_pushButtonMul_clicked()
{
    QString str= "*";
    AddChar(str);
}

void MainWindow::on_pushButton0_clicked()
{
    QString str= "0";
    AddChar(str);
}

void MainWindow::on_pushButtonPoint_clicked()
{
    QString str= ".";
    AddChar(str);
}

void MainWindow::on_pushButtonDiv_clicked()
{
    QString str= "/";
    AddChar(str);
}

void MainWindow::on_pushButtonLeft_clicked()
{
    QString str= "(";
    AddChar(str);
}

void MainWindow::on_pushButtonRight_clicked()
{
    QString str= ")";
    AddChar(str);
}
/*AddChar函数，将点击计算器按钮输入的数进行入栈操作
 */
void MainWindow::AddChar(QString ch)
{
    if(flag==1)
    {
        ui->text_screen->setText(ch);
        cal.data.push_back(ch);

        flag = 3;
    }
    else if(flag==2)
    {
        if(ui->text_screen->toPlainText()=="错误")
        {
            ui->text_screen->setText(ch);
            cal.clearVector();
            cal.data.push_back(ch);

            flag = 3;
        }
         else if(ch=="+" || ch=="-" || ch=="*" || ch=="/")
        {
             ui->text_screen->setText(ui->text_screen->toPlainText()+ch);
             cal.data.push_back(ch);

             flag = 3;
        }
         else
         {
             ui->text_screen->setText(ch);
             cal.clearVector();
             cal.data.push_back(ch);

             flag = 3;
         }

    }
    else
    {
        ui->text_screen->setText(ui->text_screen->toPlainText()+ch);
        cal.data.push_back(ch);

    }

}

void MainWindow::on_pushButtonEqual_clicked()
{
    if(cal.firstcalCulate())
    {
        if(cal.secondCalculate())
        {
            QString str = "q";
            QString answer = cal.ThirdCalculate(str);
            ui->text_screen->setText(answer);

            flag = 2;
        }
        else
        {
            QMessageBox::information(this,"错误","输入的表达式有误，请重新确认！");
            cal.clearVector();
            ui->text_screen->setText("");
            flag = 2;
        }
    }
    else
    {
        QMessageBox::information(this,"错误","输入的表达式有误，请重新确认！");
        cal.clearVector();
        ui->text_screen->setText("");
        flag = 2;
    }
}

void MainWindow::on_pushButtonClear_clicked()
{
    cal.clearVector();
    ui->text_screen->setText("");
}

void MainWindow::on_pushButton_clicked()
{
    cal.data.pop_back();
    QString str = ui->text_screen->toPlainText();
    string str1 = str.toStdString();
    QString newStr = "";
    for(unsigned int i = 0;i<str1.length()-1;i++)
        newStr+=str1[i];
    ui->text_screen->setText(newStr);

}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"打开文件","../Calculator");
    if(filename.isEmpty())
        return;
    string file_name = filename.toStdString();
    ifstream infile2(file_name.c_str());//获取文件名
    int row = 0;
    char str[1000];
    while(!infile2.eof()){
        infile2.getline(str,sizeof(str));//一行一行读
        row++;
    }
    infile2.close();
    string text[row];
    int count = 0;
    ifstream infile;
    infile.open(file_name.c_str());
    while(getline(infile,text[count])){
        count++;
    }
    infile.close();


    QString result[row];//存结果
    for(int i=0;i<row;i++){
        for(unsigned int j=0;j<text[i].length();j++){
            string current = "";
            current+=text[i][j];//将表达式存到二维数组里，然后分别提取出来压入栈中
            QString newCurrent = QString::fromStdString(current);
            AddChar(newCurrent);
        }
        cal.firstcalCulate();
        cal.secondCalculate();
        cal.ThirdCalculate(result[i]);

        cal.clearVector();
    }
    QString FinalResult;
   for(int i=0;i<row;i++){
       FinalResult+=QString::fromStdString(text[i]);
       FinalResult+=tr(" = ");
       FinalResult+=result[i];
       FinalResult+=tr("\n");
   }
   ui->text_screen->setText(FinalResult);

}
