#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDockWidget>
#include "mcl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update_status_bar_coords(double lat, double lon);
    void status_point(double lat, double lon, QgsFeatureId fid);


private slots:
    void clickedbutton();
    void choosenoption(int index);
    void lat_input(QString str);
    void lon_input(QString str);
    void trj_input(QString str);
    void point_num(QString str);
    void type_option(int index);
    void clickedaddbutton();
    void clickeddelbutton();
    void opendb();
private:


private:
        QgsVectorLayer* type_layer = new QgsVectorLayer("Point", "Points","memory");
        QgsVectorLayer* linea = new QgsVectorLayer("LineString?crs=epsg:4326&field=id:integer&index=yes","Trajectories","memory");
        QgsVectorLayer* vl = new QgsVectorLayer("/home/mihail/dev/Rossiya_Demogr.shp", "Main Layer");

        enum TYPES {
            type1,
            type2,
            type3,
        };

        int param = 0;

        int num_points = 0;
        int num_trjs = 0;

        std::map<int, QVector<QgsPoint>> trj_to_point;
        std::map<int, QgsFeatureId> trj_to_fid;
        std::map<std::tuple<double, double, int>, QgsFeatureId> xytr_to_fid;

        double curr_x;
        double curr_y;
        int curr_trj;
        int curr_num;
        TYPES curr_type = TYPES::type1;

        Ui::MainWindow *ui;

        QPushButton* button;
        QPushButton* button2;


        QLineEdit* lat;
        QLineEdit* lon;
        QLineEdit* trj;
        QComboBox* type;

        QComboBox* box;
        MCL canv =  MCL(this);


        QPushButton* add_button;
        QPushButton* del_button;

        QDialog* dialog;
        QDialogButtonBox* btn_box;


        QgsLayerTree* tree;
        QgsLayerTreeModel* treemodel;
        QgsLayerTreeView* treeview;
        QgsLayerTreeMapCanvasBridge* bridge;


        QToolBar* toolbar;

        QLineEdit* num;
};
#endif // MAINWINDOW_H
