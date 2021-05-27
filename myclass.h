#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsmaplayer.h>
#include <qgsfeature.h>
#include <qgsproviderregistry.h>
#include <qgsfield.h>
#include <qgssymbol.h>
#include <qgsfeaturesource.h>
#include <qgsproject.h>
#include <qgscoordinatereferencesystem.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsvectorfilewriter.h>
#include <qgsattributes.h>
#include <qgsrectangle.h>
#include <QMainWindow>
#include "mainwindow.h"


class MyClass : public QgsMapCanvas{
public:
    MyClass(MainWindow* w);
};


