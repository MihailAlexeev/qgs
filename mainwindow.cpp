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
    dock->setMaximumWidth(143);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWindowTitle("Choose CRS");

    QWidget* top_widg = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout();


    box = new QComboBox(dock);
    box->setMaximumWidth(135);
    box->insertItem(0, "WGS84");
    box->insertItem(1, "Web Mercator");
    connect(box, SIGNAL(activated(int)), this, SLOT(choosenoption(int)));


    button = new QPushButton(dock);
    button->setMaximumWidth(135);
    button->setText("OK");
    connect(button, SIGNAL(clicked()), this, SLOT(clickedbutton()));

    lay->addWidget(box);
    lay->addWidget(button);

    top_widg->setLayout(lay);

    dock->setWidget(top_widg);


    addDockWidget(Qt::RightDockWidgetArea, dock);


    QDockWidget* dock1 = new QDockWidget(this);
    dock1->setMaximumWidth(143);
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock1->setWindowTitle("Set Single Point");

    QWidget* top_widg1 = new QWidget();
    QHBoxLayout* lay1 = new QHBoxLayout();



    lat = new QLineEdit(dock1);
    lat->setPlaceholderText("lat");
    lat->setMaximumWidth(40);
    connect(lat, SIGNAL(textChanged(QString)), this, SLOT(lat_input(QString)));

    lon = new QLineEdit(dock1);
    lon->setPlaceholderText("lon");
    lon->setMaximumWidth(40);
    connect(lon, SIGNAL(textChanged(QString)), this, SLOT(lon_input(QString)));

    trj = new QLineEdit(dock1);
    trj->setPlaceholderText("trj");
    trj->setMaximumWidth(40);
    connect(trj, SIGNAL(textChanged(QString)), this, SLOT(trj_input(QString)));

    type = new QComboBox(dock1);
    type->setMaximumWidth(135);
    type->insertItem(0, "Type 1");
    type->insertItem(1, "Type 2");
    type->insertItem(2, "Type 3");
    connect(type, SIGNAL(activated(int)), this, SLOT(type_option(int)));

    button2 = new QPushButton(dock1);
    button2->setMaximumWidth(135);
    button2->setText("OK");
    connect(button2, SIGNAL(clicked()), this, SLOT(clickedbutton2()));





    lay1->addWidget(lat);
    lay1->addWidget(lon);
    lay1->addWidget(trj);
    QVBoxLayout* lay_d = new QVBoxLayout();
    lay_d->addLayout(lay1);
    lay_d->addWidget(type);
    lay_d->addWidget(button2);


    top_widg1->setLayout(lay_d);

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
    canv.zoomToFullExtent();
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
    xys.push_back(std::make_pair(curr_x, curr_y));
    trj_and_type.push_back(std::make_pair(curr_trj, curr_type));
    QgsFeature feat;
    feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(xys.back().first, xys.back().second)));

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
    lat->clear();
    lon->clear();
    trj->clear();
}


void MainWindow::lat_input(QString str) {
    std::string s = str.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it)) {
            return;
        }
    }
    std::istringstream is(s);
    is >> curr_x;
}

void MainWindow::lon_input(QString str1) {
    std::string s = str1.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it)) {
            return;
        }
    }
    std::istringstream is(s);
    is >> curr_y;
}

void MainWindow::trj_input(QString str2) {
    std::string s = str2.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it)) {
            return;
        }
    }
    std::istringstream is(s);
    is >> curr_trj;
}

void MainWindow::type_option(int index) {
     switch (index)
     {
     case 0:
         curr_type = TYPES::type1;
         break;
     case 1:
         curr_type = TYPES::type2;
         break;
     case 2:
         curr_type = TYPES::type3;
         break;
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}