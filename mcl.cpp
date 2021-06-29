#include "mcl.h"

MCL::MCL(QWidget *parent) : QgsMapCanvas(parent), vl("/home/mihail/dev/Rossiya_Demogr.shp")
{

QList<QgsMapLayer*> list_;
list_.append(&vl);

this->setLayers(list_);
this->setExtent(vl.extent());

setMouseTracking(true);

}

QgsVectorLayer& MCL::GetLayer() {
    return vl;
}

void MCL::mouseMoveEvent(QMouseEvent *event){
     cursor_point = this->getCoordinateTransform()->toMapCoordinates(event->pos().x(),event->pos().y());
     emit send_coords(cursor_point.x(), cursor_point.y());
     //std::cout << cursor_point.x() << " " << cursor_point.y() << std::endl;
}

std::pair<double, double> MCL::GetCoords() {
    return std::make_pair(curr_x, curr_y);
}

MCL::~MCL() {

}
