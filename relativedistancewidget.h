#ifndef RELATIVEDISTANCEWIDGET_H
#define RELATIVEDISTANCEWIDGET_H

#include <QTableWidget>
#include <QObject>
#include <QWidget>
#include "granite_traj/trajectorycalc/translations.h"
#include <qlabel.h>
#include <QVBoxLayout>

class RelativeDistanceWidget : public QWidget
{
    Q_OBJECT
public:
    RelativeDistanceWidget(QWidget *parent = nullptr);
    ~RelativeDistanceWidget();
public slots:
    void getShipCoords(const std::vector<TrajData> &trajectories);
    void getOtherObjsCoords(int id, double latitude, double longitude, double altitude);
    double calculateRDistance(double latitude, double longitude, double altitude);
private:
    GeodeticCoordinates geod_ship;
    double x_ship, y_ship, z_ship;
    int ship_id;
    QTableWidget* table;
    QLabel* label;

};

#endif // RELATIVEDISTANCEWIDGET_H
