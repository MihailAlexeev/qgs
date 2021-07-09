#include "mcl.h"

MCL::MCL(QWidget *parent) : QgsMapCanvas(parent)
{


    setMouseTracking(true);

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
