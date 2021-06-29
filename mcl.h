#ifndef MCL_H
#define MCL_H
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
#include <qgsmarkersymbollayer.h>
#include <qgslinesymbollayer.h>
#include <qgslayoutitemlabel.h>
#include <qgsprintlayout.h>
#include <qgslayout.h>
#include <qgslabeling.h>
#include <qgsfield.h>
#include <qgsvectorlayerlabeling.h>
#include <qgspallabeling.h>
#include <qgstextformat.h>
#include <qgsmapmouseevent.h>
#include <qgsmaptoolemitpoint.h>
#include <qgscategorizedsymbolrenderer.h>
#include <qlabel.h>

#include <QObject>

class MCL : public QgsMapCanvas {
    Q_OBJECT

public:

    void mouseMoveEvent(QMouseEvent *event);

    MCL(QWidget *parent = nullptr);
    QgsVectorLayer& GetLayer();
    std::pair<double, double> GetCoords();
    QgsPointXY cursor_point;
    virtual ~MCL();
signals:
    void send_coords(double lat, double lon);

private:
    QgsVectorLayer vl;
    double curr_x;
    double curr_y;

};

#endif // MCL_H
