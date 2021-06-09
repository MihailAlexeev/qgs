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

private slots:
    void clickedbutton();
    void choosenoption(int index);
    void clickedbutton2();
    void lat_input(QString str);
    void lon_input(QString str);
    void trj_input(QString str);
    void type_option(int index);

private:
        QgsVectorLayer* additional_layer = new QgsVectorLayer("Point", "temp_points","memory");

        enum TYPES {
            type1,
            type2,
            type3,
        };


        int param;
        std::vector<std::pair<double, double>> xys;
        std::vector<std::pair<int, TYPES>> trj_and_type;

        double curr_x;
        double curr_y;
        int curr_trj;
        TYPES curr_type;

        Ui::MainWindow *ui;

        QPushButton* button;
        QPushButton* button2;

        QLineEdit* lat;
        QLineEdit* lon;
        QLineEdit* trj;
        QComboBox* type;

        QComboBox* box;
        MCL canv = MCL(this);

};
#endif // MAINWINDOW_H
