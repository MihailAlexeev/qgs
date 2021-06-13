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


class MCL : public QgsMapCanvas {
public:
    void mousePressEvent(QMouseEvent* e) override;

    MCL(QWidget *parent = nullptr);
    QgsVectorLayer& GetLayer();
private:
    QgsVectorLayer vl;

};

#endif // MCL_H
