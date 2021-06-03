#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <iostream>
#include <string>
#include <sstream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QDockWidget* dock = new QDockWidget(this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWindowTitle("Choose CRS");

    QWidget* top_widg = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout();


    box = new QComboBox(dock);
    box->insertItem(0, "WGS84");
    box->insertItem(1, "World Mercator");
    connect(box, SIGNAL(activated(int)), this, SLOT(choosenoption(int)));


    button = new QPushButton(dock);
    button->setText("OK");
    connect(button, SIGNAL(clicked()), this, SLOT(clickedbutton()));

    lay->addWidget(box);
    lay->addWidget(button);

    top_widg->setLayout(lay);

    dock->setWidget(top_widg);


    addDockWidget(Qt::RightDockWidgetArea, dock);


    QDockWidget* dock1 = new QDockWidget(this);
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock1->setWindowTitle("Set Single Point");

    QWidget* top_widg1 = new QWidget();
    QVBoxLayout* lay1 = new QVBoxLayout();

    line = new QLineEdit(dock1);
    connect(line, SIGNAL(textChanged(QString)), this, SLOT(lineinput(QString)));

    button2 = new QPushButton(dock1);
    button2->setText("OK");
    connect(button2, SIGNAL(clicked()), this, SLOT(clickedbutton2()));


    lay1->addWidget(line);
    lay1->addWidget(button2);

    top_widg1->setLayout(lay1);

    dock1->setWidget(top_widg1);

    addDockWidget(Qt::RightDockWidgetArea, dock1);


    ui->setupUi(this);


}


void MainWindow::clickedbutton() {
     if (param == 0) {
         std::cout << "WGS" << std::endl;
     }
     if (param == 1) {
         std::cout << "Merc" << std::endl;
     }
}

void MainWindow::choosenoption(int index) {
     if (index == 0) {
         param = 0;
     }
     if (index == 1) {
         param = 1;
     }
}


void MainWindow::clickedbutton2() {
    std::cout << x << " " << y << std::endl;
}


void MainWindow::lineinput(QString str) {
    std::istringstream is(str.toStdString());
    is >> x >> y;
}


MainWindow::~MainWindow()
{
    delete ui;
}
