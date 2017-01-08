#ifndef CALCULATE_H
#define CALCULATE_H

#include <Qstring>
#include <QApplication>
#include <QDialog>
#include <QVector>
#include <QtCore/qmath.h>
#include <QDebug>
#include <QStack>
#include <QRegExp>
#include <QVector>


class Calculate
{
public:
    Calculate();
    ~Calculate();
    bool firstcalCulate();
    bool secondCalculate();
    QString ThirdCalculate(QString& qwe);
    void clearVector();
    QVector<QString> data;
    QVector<QString> tempdata;
    QStack<QString> data2;
    QStack<QString> data3;
};

#endif // CALCULATE_H
