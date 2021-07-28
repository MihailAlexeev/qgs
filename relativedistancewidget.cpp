#include "relativedistancewidget.h"

RelativeDistanceWidget::RelativeDistanceWidget(QWidget *parent) : QWidget(parent){
    QVBoxLayout* lay = new QVBoxLayout;
    label = new QLabel;
    label->setText("SHIP COORDS: ");
    table = new QTableWidget;
    table->setRowCount(1);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Object ID", "Relative distance", "Coordinates"});
    lay->addWidget(label);
    lay->addWidget(table);
    this->setLayout(lay);
}

RelativeDistanceWidget::~RelativeDistanceWidget() {
    delete table;
    delete label;
}

void RelativeDistanceWidget::getShipCoords(const std::vector<TrajData> &trajectories) {
    for (const auto& i : trajectories) {
        if (i.type == SHIP) {
            ship_id = i.numTr;
            for (const auto& e : i.coords) {
                geod_ship.latitude = e.latitude;
                geod_ship.longitude = e.longitude;
                geod_ship.altitude = e.altitude;
            }
        }
    }
    auto geoc_ship = GeodeticToGeocentric(geod_ship);
    x_ship = geoc_ship.x_;
    y_ship = geoc_ship.y_;
    z_ship = geoc_ship.z_;
    label->setText("SHIP COORDS: " + QString::number(geod_ship.latitude) + ", " + QString::number(geod_ship.longitude));
}

void RelativeDistanceWidget::getOtherObjsCoords(int id, double latitude, double longitude, double altitude) {
    if (id != ship_id) {
//        table->setItem(id + 2, 0, new QTableWidgetItem(QString::number(id)));
//        double dist = calculateRDistance(latitude, longitude, altitude);
//        table->setItem(id + 2, 1, new QTableWidgetItem(QString::number(dist)));
//        table->setItem(id + 2, 2, new QTableWidgetItem(QString::number(latitude) + " " + QString::number(longitude) + " " + QString::number(altitude)));
    }
}

double RelativeDistanceWidget::calculateRDistance(double latitude, double longitude, double altitude) {
    auto geoc = GeodeticToGeocentric({latitude, longitude, altitude});
    return std::sqrt((x_ship - geoc.x_)*(x_ship - geoc.x_) + (y_ship - geoc.y_)*(y_ship - geoc.y_) + (z_ship - geoc.z_)*(z_ship - geoc.z_));
}






