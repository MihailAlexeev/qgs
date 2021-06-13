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
    QgsMarkerSymbol* s1 = QgsMarkerSymbol::createSimple({{"name", "circle"}, {"color", "white"}});
    QgsSingleSymbolRenderer* r1 = new QgsSingleSymbolRenderer (s1);
    QgsMarkerSymbol* s2 = QgsMarkerSymbol::createSimple({{"name", "circle"}, {"color", "blue"}});
    QgsSingleSymbolRenderer* r2 = new QgsSingleSymbolRenderer (s2);
    QgsMarkerSymbol* s3 = QgsMarkerSymbol::createSimple({{"name", "circle"}, {"color", "red"}});
    QgsSingleSymbolRenderer* r3 = new QgsSingleSymbolRenderer (s3);
    type1_layer->setRenderer(r1);
    type2_layer->setRenderer(r2);
    type3_layer->setRenderer(r3);

    QgsLineSymbol* s4 = QgsLineSymbol::createSimple({{"color", "black"}});
    QgsSingleSymbolRenderer* r4 = new QgsSingleSymbolRenderer (s4);
    linea->setRenderer(r4);


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
    xys.push_back({curr_x, curr_y});
    trj_and_type.push_back(std::make_pair(curr_trj, curr_type));

    trj_to_point[curr_trj].push_back(xys.back());
    linea->startEditing();
    QgsFeature line;

    line.setGeometry(QgsGeometry::fromPolyline(trj_to_point[curr_trj]));
    line.setAttributes({1});
    linea->addFeature(line);
    linea->commitChanges();

    QgsFeature feat;
    feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(xys.back().x(), xys.back().y())));




    if (curr_type == TYPES::type1) {

        type1_layer->startEditing();
        type1_layer->addFeature(feat);
        type1_layer->updateExtents();




        type1_layer->commitChanges();
    } else if (curr_type == TYPES::type2) {
        type2_layer->startEditing();
        type2_layer->addFeature(feat);
        type2_layer->updateExtents();



        type2_layer->commitChanges();
    } else {
        type3_layer->startEditing();
        type3_layer->addFeature(feat);
        type3_layer->updateExtents();



        type3_layer->commitChanges();
    }


    QList<QgsMapLayer*> list;
    list.append({type1_layer, type2_layer, type3_layer});
    list.append(linea);
    list.append(&canv.GetLayer());

    canv.setExtent(canv.GetLayer().extent());
    canv.setLayers(list);

    lat->clear();
    lon->clear();
    trj->clear();
}


void MainWindow::lat_input(QString str) {
    std::string s = str.toStdString(); 
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it)) {
            throw std::invalid_argument("LAT IS DOUBLE");
        }
    }
    std::istringstream is(s);
    is >> curr_x;
}

void MainWindow::lon_input(QString str1) {
    std::string s = str1.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it)) {
            throw std::invalid_argument("LON IS DOUBLE");
        }
    }
    std::istringstream is(s);

    is >> curr_y;
}

void MainWindow::trj_input(QString str2) {
    std::string s = str2.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it)) {
            throw std::invalid_argument("TRJ IS INT");
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


