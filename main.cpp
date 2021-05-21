#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <qgis/qgsmapcanvas.h>
#include <qgis/qgsvectorlayer.h>
#include <qgis/qgsmaplayer.h>
#include <qgis/qgsfeature.h>
#include <qgis/qgsproviderregistry.h>
#include <qgis/qgsfield.h>
#include <qgis/qgssymbol.h>
#include <qgis/qgsfeaturesource.h>
#include <qgis/qgsproject.h>
#include <QtDebug>
#include <stdio.h>
#include <qgis/qgssinglesymbolrenderer.h>
//#include <qgis/qgsvectorfilewriter.h>
#include "myclass.h"
#include <QVariant>


using namespace std;

int main(int argc, char *argv[])
{
    QgsProviderRegistry::instance( QString("%1/plugins").arg(QDir::currentPath()) );
    QApplication a(argc, argv);

//        QgsVectorLayer vl("/home/mikhail/dev/Rossiya_Demogr.shp");


        QgsVectorLayer layer("Point", "temp_points","memory");

        QgsField f1("name", QVariant::String);
        QgsField f2("age", QVariant::Int);
        layer.startEditing();

        layer.addAttribute(f1);
        layer.addAttribute(f2);
        layer.updateFields();


        QgsFeature feat;
        feat.setGeometry(QgsGeometry::fromPointXY(QgsPointXY(100,100)));

        QVector<QVariant> qv = {"John", 100};
        QgsAttributes attrs(qv);
        feat.setAttributes(attrs);

        cout << layer.addFeature(feat) << endl;
        layer.updateExtents();

        QgsSymbol* sym = QgsSymbol::defaultSymbol(layer.geometryType());
        QgsSingleSymbolRenderer* renderer = new QgsSingleSymbolRenderer (sym->clone());
        layer.setRenderer(renderer);


        QList<QgsMapLayer*> list_;
        list_.append(&layer);
        QgsMapCanvas m_canvas;
        m_canvas.setExtent(layer.extent());
        m_canvas.setLayers(list_);
        m_canvas.show();


    //    MainWindow w;
    //    w.setCentralWidget(&m);


    //    w.show();

    return a.exec();
}
