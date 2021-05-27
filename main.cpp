#include "mainwindow.h"
#include "myclass.h"
#include <QApplication>
#include <QtDebug>
#include <stdio.h>
#include <QVariant>
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    MyClass m(&w);

    w.show();

    return a.exec();
}
