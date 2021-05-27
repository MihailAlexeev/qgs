#include "myclass.h"

using namespace std;

MyClass::MyClass(MainWindow* w) {
    QgsProviderRegistry::instance( QString("%1/plugins").arg(QDir::currentPath()) );
    QgsVectorLayer vl("/home/mihail/dev/Rossiya_Demogr.shp");
    QgsVectorLayer layer("Point", "temp_points","memory");

    layer.startEditing();

    QgsField f1("name", QVariant::String);
    QgsField f2("age", QVariant::Int);

    layer.addAttribute(f1);
    layer.addAttribute(f2);

    QgsFeature feat;

    feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(0, 0)));

    QVector<QVariant> qv = {"John", 100};

    QgsAttributes attrs(qv);

    feat.setAttributes(attrs);

    layer.addFeature(feat);

    layer.updateExtents();

    QgsSymbol* s = QgsSymbol::defaultSymbol(layer.geometryType());
    QgsSingleSymbolRenderer* r = new QgsSingleSymbolRenderer (s->clone());

    layer.setRenderer(r);

    auto CRS = vl.crs();
    layer.setCrs(CRS);
    cout << vl.crs().description().toStdString() << endl;
    cout << layer.crs().description().toStdString() << endl;

    layer.commitChanges();

    vl.commitChanges();

    QList<QgsMapLayer*> list_;
    list_.append(&vl);
    list_.append(&layer);

    this->setLayers(list_);
    this->setExtent(vl.extent());

    w->setCentralWidget(this);

    cout << this->center() << endl;
}
