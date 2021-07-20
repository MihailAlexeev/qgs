#include "mcl.h"

MCL::MCL(QWidget *parent) : QgsMapCanvas(parent)
{
    setMouseTracking(true);
    tool = new  QgsMapToolIdentifyFeature(this);
    this->setMapTool(tool);
}





void MCL:: mousePressEvent(QMouseEvent *e) {
    auto feature = tool->identify(e->pos().x(), e->pos().y(),
                                  this->layers(), QgsMapToolIdentify::TopDownAll);
    for (auto x : feature) {
        if (x.mFeature.geometry().type() == QgsWkbTypes::GeometryType::PointGeometry) {
            emit send_p(x.mFeature.geometry().asPoint().x(), x.mFeature.geometry().asPoint().y(), x.mFeature.id());
        }

    }
}

void MCL::mouseMoveEvent(QMouseEvent *event){
     cursor_point = this->getCoordinateTransform()->toMapCoordinates(event->pos().x(),event->pos().y());
     emit send_coords(cursor_point.x(), cursor_point.y());
}

std::pair<double, double> MCL::GetCoords() {
    return std::make_pair(curr_x, curr_y);
}

MCL::~MCL() {

}
