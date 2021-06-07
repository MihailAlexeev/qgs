#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mcl.h"
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
    box->insertItem(1, "Web Mercator");
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
    setCentralWidget(&canv);

}


void MainWindow::clickedbutton() {
    if (param == 0) {
        std::cout << "EPSG:4326" << std::endl;
        QgsCoordinateReferenceSystem crs("EPSG:4326");
        canv.setDestinationCrs(crs);
        canv.refresh();
    }
    if (param == 1) {
        std::cout << "EPSG:3857" << std::endl;
        QgsCoordinateReferenceSystem crs("EPSG:3857");
        canv.setDestinationCrs(crs);
        canv.refresh();
    }


}

void MainWindow::choosenoption(int index) {
     switch (index)
     {
     case 0:
         param = 0;
         break;
     case 1:
         param = 1;
         break;
     }
}


void MainWindow::clickedbutton2() {
    QgsFeature feat;
    feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(x, y)));

    additional_layer->startEditing();
    additional_layer->addFeature(feat);
    additional_layer->updateExtents();

    QgsSymbol* s = QgsSymbol::defaultSymbol(additional_layer->geometryType());
    QgsSingleSymbolRenderer* r = new QgsSingleSymbolRenderer (s->clone());
    additional_layer->setRenderer(r);
    additional_layer->commitChanges();

    QList<QgsMapLayer*> list;
    list.append(&canv.GetLayer());
    list.append(additional_layer);

    canv.setLayers(list);
    line->clear();
}


void MainWindow::lineinput(QString str) {
    std::istringstream is(str.toStdString());
    is >> x >> y;
}


MainWindow::~MainWindow()
{
    delete ui;
}
