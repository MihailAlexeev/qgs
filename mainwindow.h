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

private slots:
    void clickedbutton();
    void choosenoption(int index);
    void clickedbutton2();
    void lat_input(QString str);
    void lon_input(QString str);
    void trj_input(QString str);
    void type_option(int index);



private:
        QgsVectorLayer* type_layer = new QgsVectorLayer("Point", "temp_points","memory");
        QgsVectorLayer* linea = new QgsVectorLayer("LineString?crs=epsg:4326&field=id:integer&index=yes","Linea","memory");

        enum TYPES {
            type1,
            type2,
            type3,
        };

        int param = 0;
        std::vector<QgsPoint> xys;
        std::vector<std::pair<int, TYPES>> trj_and_type;

        std::map<int, QVector<QgsPoint>> trj_to_point;

        double curr_x;
        double curr_y;
        int curr_trj;
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



};
#endif // MAINWINDOW_H
