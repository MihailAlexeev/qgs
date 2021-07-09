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
    type_layer->startEditing();
    type_layer->dataProvider()->addAttributes({QgsField("fid", QVariant::Int),
                                         QgsField("ftype", QVariant::Int)});
    type_layer->updateFields();

    type_layer->setLabelsEnabled(true);
    QgsPalLayerSettings pls;
    pls.fieldName = "fid";
    pls.placement = QgsPalLayerSettings::Placement::Line;
    QgsVectorLayerSimpleLabeling* simple_label = new QgsVectorLayerSimpleLabeling(pls);
    type_layer->setLabeling(simple_label);

    QgsMarkerSymbol* s1 = QgsMarkerSymbol::createSimple({{"name", "circle"}, {"color", "white"}});
    QgsMarkerSymbol* s2 = QgsMarkerSymbol::createSimple({{"name", "circle"}, {"color", "blue"}});
    QgsMarkerSymbol* s3 = QgsMarkerSymbol::createSimple({{"name", "circle"}, {"color", "red"}});


    QgsRendererCategory cat1("1", s1, "1");
    QgsRendererCategory cat2("2", s2, "2");
    QgsRendererCategory cat3("3", s3, "3");
    QgsCategorizedSymbolRenderer* cat_rend = new QgsCategorizedSymbolRenderer("ftype", {cat1, cat2, cat3});
    type_layer->setRenderer(cat_rend);


    type_layer->commitChanges();

    QgsLineSymbol* s4 = QgsLineSymbol::createSimple({{"color", "black"}});
    QgsSingleSymbolRenderer* r4 = new QgsSingleSymbolRenderer (s4);
    linea->setRenderer(r4);


    QDockWidget* dock = new QDockWidget(this);
    dock->setMaximumWidth(200);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWindowTitle("Choose CRS");

    QWidget* top_widg = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout();


    box = new QComboBox(dock);
    box->setMaximumWidth(150);
    box->insertItem(0, "WGS84");
    box->insertItem(1, "Web Mercator");
    connect(box, SIGNAL(activated(int)), this, SLOT(choosenoption(int)));


    button = new QPushButton(dock);
    button->setMaximumWidth(150);
    button->setText("OK");
    connect(button, SIGNAL(clicked()), this, SLOT(clickedbutton()));

    lay->addWidget(box);
    lay->addWidget(button);

    top_widg->setLayout(lay);

    dock->setWidget(top_widg);


    addDockWidget(Qt::RightDockWidgetArea, dock);

    QDockWidget* dock2 = new QDockWidget(this);
    QWidget* top_widg2 = new QWidget();
    dock2->setMaximumWidth(200);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock2->setWindowTitle("Слои");

    QgsProject::instance()->addMapLayer(vl);

    treeview = new QgsLayerTreeView(dock2);
    treemodel = new QgsLayerTreeModel(QgsProject::instance()->layerTreeRoot());
    treemodel->setFlag(QgsLayerTreeModel::AllowNodeRename);
    treemodel->setFlag(QgsLayerTreeModel::AllowNodeReorder);
    treemodel->setFlag(QgsLayerTreeModel::AllowNodeChangeVisibility);
    treemodel->setFlag(QgsLayerTreeModel::ShowLegendAsTree);
    treemodel->setAutoCollapseLegendNodes(10);
    treeview->setModel(treemodel);
    bridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(), &canv);


    add_button = new QPushButton(dock2);

    QHBoxLayout* lay2 = new QHBoxLayout();
    add_button->setText("+");
    add_button->setToolTip("Добавить точку");
    lay2->addWidget(add_button);
    connect(add_button, SIGNAL(clicked()), this, SLOT(clickedaddbutton()));

    QVBoxLayout* lay_v = new QVBoxLayout();
    lay_v->addLayout(lay2);
    lay_v->addWidget(treeview);

    top_widg2->setLayout(lay_v);

    dock2->setWidget(top_widg2);

    addDockWidget(Qt::RightDockWidgetArea, dock2);


    canv.setExtent(vl->extent());
    canv.setLayers({vl});

    ui->setupUi(this);
    setCentralWidget(&canv);


    connect(&canv, &MCL::send_coords, this, &MainWindow::update_status_bar_coords);

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
    canv.zoomToSelected(vl);
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





void MainWindow::lat_input(QString str) {
    std::string s = str.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it) && *it != '-' && *it != '.') {
            throw std::invalid_argument("LAT IS DOUBLE");
        }
    }
    std::istringstream is(s);
    is >> curr_x;
}

void MainWindow::lon_input(QString str1) {
    std::string s = str1.toStdString();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (!std::isdigit(*it) && *it != '-' && *it != '.') {
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
            throw std::invalid_argument("TRJ IS POS INT");
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

void MainWindow::update_status_bar_coords(double lat, double lon)
{
    ui->statusbar->showMessage("LAT: " + QString().setNum(lat) + " LON: " + QString().setNum(lon));
}


void MainWindow::clickedaddbutton() {
    dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Добавить точку"));

    btn_box = new QDialogButtonBox(dialog);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btn_box, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    lat = new QLineEdit(dialog);
    lat->setPlaceholderText("lat");
    lat->setMaximumWidth(40);
    connect(lat, SIGNAL(textChanged(QString)), this, SLOT(lat_input(QString)));

    lon = new QLineEdit(dialog);
    lon->setPlaceholderText("lon");
    lon->setMaximumWidth(40);
    connect(lon, SIGNAL(textChanged(QString)), this, SLOT(lon_input(QString)));

    trj = new QLineEdit(dialog);
    trj->setPlaceholderText("trj");
    trj->setMaximumWidth(40);
    connect(trj, SIGNAL(textChanged(QString)), this, SLOT(trj_input(QString)));

    type = new QComboBox(dialog);
    type->setMaximumWidth(135);
    type->insertItem(0, "Type 1");
    type->insertItem(1, "Type 2");
    type->insertItem(2, "Type 3");
    connect(type, SIGNAL(activated(int)), this, SLOT(type_option(int)));

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(lat);
    lay->addWidget(lon);
    lay->addWidget(trj);
    lay->addWidget(type);
    QVBoxLayout* lay1 = new QVBoxLayout();
    lay1->addLayout(lay);

    lay1->addWidget(btn_box);
    dialog->setLayout(lay1);
    dialog->show();
    if (dialog->exec() == QDialog::Accepted) {

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
        feat.setFields(type_layer->fields());
        feat.setAttributes({QVariant::Int, QVariant::Int});
        int i = xys.size();
        feat.setAttribute("fid", i);
        if (curr_type == TYPES::type1) {
            feat.setAttribute("ftype", 1);
        }
        if (curr_type == TYPES::type2) {
            feat.setAttribute("ftype", 2);
        }
        if (curr_type == TYPES::type3) {
            feat.setAttribute("ftype", 3);
        }

        feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(xys.back().x(), xys.back().y())));
        type_layer->startEditing();
        type_layer->addFeature(feat);
        type_layer->updateExtents();
        type_layer->commitChanges();


        QList<QgsMapLayer*> list;
        list.append(type_layer);    
        list.append(linea);
        list.append(vl);
        QgsProject::instance()->addMapLayer(type_layer);
        QgsProject::instance()->addMapLayer(linea);
        canv.setExtent(vl->extent());
        canv.setLayers(list);



        lat->clear();
        lon->clear();
        trj->clear();

        canv.zoomToSelected(vl);
    }

}



MainWindow::~MainWindow()
{
    delete ui;
}


