#include "mainwindow.h"
#include "mcl.h"
#include <QApplication>
#include <QtDebug>
#include <stdio.h>
#include <QVariant>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
    {
    QApplication a(argc, argv);
    QgsProviderRegistry::instance( QString("%1/plugins").arg(QDir::currentPath()) );

    MainWindow w;

    w.show();

    return a.exec();
    }
