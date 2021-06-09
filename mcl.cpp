#include "mcl.h"

MCL::MCL(QWidget *parent) : QgsMapCanvas(parent), vl("/home/mihail/dev/Rossiya_Demogr.shp")
{

QList<QgsMapLayer*> list_;
list_.append(&vl);

this->setLayers(list_);
this->setExtent(vl.extent());

}

QgsVectorLayer& MCL::GetLayer() {
    return vl;
}
